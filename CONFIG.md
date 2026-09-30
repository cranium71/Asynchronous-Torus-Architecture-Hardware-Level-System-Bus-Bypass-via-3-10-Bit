# Local Framework Customization & Multi-Core Protection / Helyi Rendszer és Magvédelem

HU: Az exe fájl automatikusan feltérképezi a PC CPU és GPU szerkezetét. A legjobb tudásom szerint úgy állítottam be,
hogy optimális és alkalmas legyen minden elegendő maggal rendelkező PC-hez. Hibajavítással nem foglalkoztam, arról
gondoskodj magad! Ha a géped nem megfelelő, találd ki, hogyan alakítod át a saját igényeidre! 
FIGYELJ: Ne maradjon szabadon egy CPU mag sem! Minden magot legalább egy alap védelemmel el kell látni, mert például
2 GPU esetén a másik halálra pörög, nem tudja tartani a tempót! A felelősség szigorúan a felhasználóé!

---

## English
The compiled executable automatically maps and profiles the local PC's CPU and GPU architecture. It is optimized for any
PC with a sufficient core count. Bug fixing and error handling are your responsibility; adapt the framework to your needs
if your hardware is inadequate.
CRITICAL HARDWARE REQUIREMENT: Do not leave a single CPU core unprotected or unassigned! Every core must be provisioned with
at least basic thread-gating protection. In multi-GPU setups (e.g., 2 GPUs), an unprotected core will cause the secondary
GPU to spin out of control (overclock/burnout) as it fails to match the asynchronous processing tempo. The user bears all liability.

## Deutsch
Die kompilierte ausführbare Datei kartiert und profiliert automatisch die CPU- und GPU-Architektur des lokalen PCs. Es ist für jeden
PC mit ausreichender Kernanzahl optimiert. Fehlerbehebung liegt in Ihrer Verantwortung; Passen Sie das Framework an, wenn Ihre Hardware
unzureichend ist.
WICHTIGE HARDWARE-ANFORDERUNG: Lassen Sie keinen einzigen CPU-Kern ungeschützt oder unzugewiesen! Jeder Kern muss mit mindestens einem
grundlegenden Thread-Gating-Schutz ausgestattet sein. Bei Setups mit mehreren GPUs (z. B. 2 GPUs) führt ein ungeschützter Kern dazu, dass
die sekundäre GPU unkontrolliert überdreht, da sie das asynchrone Verarbeitungstempo nicht einhalten kann. Die Haftung liegt allein beim Benutzer.

## Français
L'exécutable compilé cartographie et profile automatiquement l'architecture CPU et GPU du PC local. Il est optimisé pour tout PC disposant
d'un nombre suffisant de cœurs. La correction des bogues est de votre responsabilité ; adaptez le système si votre matériel est inadéquat.
EXIGENCE MATÉRIELLE CRITIQUE : Ne laissez pas un seul cœur CPU sans protection ou non assigné ! Chaque cœur doit être doté d'au moins une
protection de base par barrière de thread. Dans les configurations multi-GPU (par exemple, 2 GPU), un cœur non protégé entraînera un emballement
thermique du second GPU, incapable de suivre le tempo du traitement asynchrone. L'utilisateur assume toute la responsabilité.

## 日本語
コンパイルされた実行ファイル（.exe）は、ローカルPCのCPUおよびGPUアーキテクチャを自動的にマッピングします。十分なコア数を備えたあらゆるPCに適応できるように設計されています。バグ修正は自己責任となりますので、環境に合わせて修正してください。
重大なハードウェア要件: 1つのCPUコアも保護されていない状態（未割り当て）で放置しないでください！すべてのコアに、少なくとも基本的なスレッド・ゲーティング保護をプロビジョニングする必要があります。マルチGPU構成（例：2枚のGPU）において、保護されていないコアが存在すると、非同期処理のテンポに追従できず、セカンダリGPUが制御不能な暴走（オーバークロック・焼き付き）を引き起こします。

## Swahili
Faili inayoweza kutekelezwa inachora na kuangazia kiotomatiki muundo wa CPU na GPU wa PC ya ndani. Imesanidiwa kuwa bora kwa PC yoyote yenye idadi
ya kutosha ya viini. Kurekebisha hitilafu ni jukumu lako; rekebisha mfumo ikiwa vifaa vyako havitoshi.
SHARTI LA KIUFUNDI LA VIFAA: Usiache hata kiini kimoja cha CPU bila kulindwa au bila kupangiwa kazi! Kila kiini lazima kiwe na ulinzi wa kimsingi
wa kuzuia nyuzi (thread-gating). Katika usanidi wa GPU nyingi (kwa mfano, GPU 2), kiini kisicholindwa kitasababisha GPU ya pili kuzunguka bila udhibiti
(kuchoma moto) kwani inashindwa kulingana na kasi ya usindikaji isiyo sawia. Majukumu yote ni ya mtumiaji.
