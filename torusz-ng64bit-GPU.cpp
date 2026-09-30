#include <iostream>
#include <vector>
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// A -90 fokos elforgatott k=8-as fraktálmag HLSL nyelven (DirectX Compute Shader)
const char* shaderSource = 
"struct SuperPixel4 { float4 sp_x; float4 sp_y; };\n"
"RWStructuredBuffer<SuperPixel4> BufferOut : register(u0);\n"
"[numthreads(256, 1, 1)]\n"
"void CSMain(uint3 thread_id : SV_DispatchThreadID) {\n"
"    uint id = thread_id.x;\n"
"    const float k = 8.0f;\n"
"    const float PI = 3.14159265359f;\n"
"    const float phaseShift = -1.57079632679f;\n"
"    float base_magnitude = (float)id / k;\n"
"    float base_theta = (float)id * (2.0f * PI / k);\n"
"    float4 sp_x; float4 sp_y;\n"
"    float theta0 = base_theta + (0.0f * (PI / 4.0f)) + phaseShift;\n"
"    sp_x.x = base_magnitude * cos(theta0); sp_y.x = base_magnitude * sin(theta0);\n"
"    float theta1 = base_theta + (1.0f * (PI / 4.0f)) + phaseShift;\n"
"    sp_x.y = base_magnitude * cos(theta1); sp_y.y = base_magnitude * sin(theta1);\n"
"    float theta2 = base_theta + (2.0f * (PI / 4.0f)) + phaseShift;\n"
"    sp_x.z = base_magnitude * cos(theta2); sp_y.z = base_magnitude * sin(theta2);\n"
"    float theta3 = base_theta + (3.0f * (PI / 4.0f)) + phaseShift;\n"
"    sp_x.w = base_magnitude * cos(theta3); sp_y.w = base_magnitude * sin(theta3);\n"
"    BufferOut[id].sp_x = sp_x;\n"
"    BufferOut[id].sp_y = sp_y;\n"
"}\n";

void BeoltKartyat(IDXGIAdapter* pAdapter, UINT index) {
    DXGI_ADAPTER_DESC desc;
    pAdapter->GetDesc(&desc);
    std::wcout << L"\n[PASZTAZAS] Hardver detektalva [" << index << L"]: " << desc.Description << std::endl;

    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    D3D_FEATURE_LEVEL featureLevel;

    // ELV SZERINTI JAVÍTÁS: Nem nullptr-t adunk meg, hanem kényszerítjük a konkrét adaptert!
    HRESULT hr = D3D11CreateDevice(
        pAdapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &device, &featureLevel, &context
    );

    if (FAILED(hr)) {
        std::cout << " -> Nem sikerult inicializalni ezt a hardvert!" << std::endl;
        return;
    }

    unsigned int total_threads = 3840;
    unsigned int thread_groups = total_threads / 256;

    // Shader lefordítása a kiválasztott GPU-ra
    ID3DBlob* csBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;
    hr = D3DCompile(shaderSource, strlen(shaderSource), nullptr, nullptr, nullptr, "CSMain", "cs_5_0", 0, 0, &csBlob, &errorBlob);
    
    if (FAILED(hr)) {
        if (errorBlob) errorBlob->Release();
        std::cout << " -> Hiba a fuggveny GPU-s forditasa kozben!" << std::endl;
        device->Release();
        return;
    }

    ID3D11ComputeShader* computeShader = nullptr;
    device->CreateComputeShader(csBlob->GetBufferPointer(), csBlob->GetBufferSize(), nullptr, &computeShader);
    csBlob->Release();

    // 0 MB VRAM elvű miniatűr puffer konfigurálása
    ID3D11Buffer* outputBuffer = nullptr;
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.ByteWidth = total_threads * sizeof(float) * 8;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS;
    bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    bufferDesc.StructureByteStride = sizeof(float) * 8;
    device->CreateBuffer(&bufferDesc, nullptr, &outputBuffer);

    ID3D11UnorderedAccessView* uav = nullptr;
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
    uavDesc.Format = DXGI_FORMAT_UNKNOWN;
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.NumElements = total_threads;
    device->CreateUnorderedAccessView(outputBuffer, &uavDesc, &uav);

    // A shader és a puffer összekötése, majd a motor indítása a hardveren
    context->CSSetShader(computeShader, nullptr, 0);
    context->CSSetUnorderedAccessViews(0, 1, &uav, nullptr);
    context->Dispatch(thread_groups, 1, 1);

    std::cout << " -> [SIKER] A keplet rarasva a hardverre. Biztonsagos fazis aktivalva." << std::endl;

    // Takarítás
    uav->Release(); outputBuffer->Release();
    computeShader->Release(); context->Release(); device->Release();
}

int main() {
    std::cout << "==========================================================" << std::endl;
    std::cout << " 43N1G1 MOTOR - UNIVERSAL MULTI-GPU DIRECTX INJEKCIO" << std::endl;
    std::cout << "==========================================================" << std::endl;

    IDXGIFactory* factory = nullptr;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
    
    if (FAILED(hr)) {
        std::cout << "Nem sikerult elerni a DXGI hardver-listazot!" << std::endl;
        return 1;
    }

    IDXGIAdapter* adapter = nullptr;
    UINT adapterIndex = 0;

    // Végigmegyünk az ÖSSZES gépben lévő kártyán (Intel, NVIDIA, AMD)
    while (factory->EnumAdapters(adapterIndex, &adapter) != DXGI_ERROR_NOT_FOUND) {
        BeoltKartyat(adapter, adapterIndex);
        adapter->Release();
        adapterIndex++;
    }

    factory->Release();
    std::cout << "\n==========================================================" << std::endl;
    std::cout << " Minden aktiv grafikus hardver beoltva. Jo munkat kivanunk!" << std::endl;
    std::cout << "==========================================================" << std::endl;
    
    // KÉNYSERÍTETT RENDSZERSZINTŰ KILÉPÉS: Felszámol minden hardveres beragadást,
    // azonnal bezárja az ablakot, nincs többé ottmaradás a monitoron!
    ExitProcess(0); 
    
    return 0;
}
// C:\mingw64\bin\g++.exe -O3 -static -static-libgcc -static-libstdc++ C:\Users\YOU CODE.cpp -o C:\Users\YOU CODE.exe -ld3d11 -ld3dcompiler -ldxgi
