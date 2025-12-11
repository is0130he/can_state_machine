
# CAN State Machine (Visual Studio Project)

本プロジェクトは、CAN フレーム受信に応じて ECU の状態遷移を行う  
**ステートマシン学習用プロジェクト（Visual Studio 版）** です。

Linux 版とは別に、Windows / Visual Studio を前提としたソース構成にてビルド可能です。

---

## 📁 プロジェクト構成

can_state_machine/
├── vs_project/ # Visual Studio 用プロジェクト
│ ├── can_state_machine.sln
│ └── src/
│ ├── app/ # ステートマシン（上位アプリ層）
│ │ ├── state_machine.c
│ │ └── state_machine.h
│ ├── driver/ # CAN ドライバ層（モック）
│ │ ├── can.c
│ │ └── can.h
│ └── service/ # 汎用サービス（イベントバッファ等）
│ ├── event_buffer.c
│ └── event_buffer.h
│ └── main.c
├── src_linux/ # Ubuntu向け旧バージョン（保持）
└── README.md

yaml
コードをコピーする

---

## 🛠 動作環境

- Windows 10 / 11  
- Visual Studio 2022  
- C 言語 (MSVC)

---

## 🚀 ビルド手順（Visual Studio）

1. Visual Studio を開く  
2. `vs_project/can_state_machine.sln` をダブルクリック  
3. メニューから  
ビルド → ソリューションのビルド

markdown
コードをコピーする
4. エラーがなければビルド成功  

---

## ▶ 実行手順

1. `Ctrl + F5` でデバッグなし実行  
2. コンソールが起動する  
3. 以下のキー入力で CAN フレームを擬似生成できます：

| 入力キー | 意味 | CAN イベント |
|---------|------|----------------|
| `r` | READY frame | READY |
| `s` | START frame | START |
| `t` | STOP frame | STOP |
| `e` | FAULT frame | FAULT |
| `x` | RESET frame | RESET |

4. ステートマシンが以下のように遷移します：

状態 : 初期化
(キー入力)
状態 : 待機
(キー入力)
状態 : 稼働中
...

yaml
コードをコピーする

---

## 🔧 ステートマシン仕様

ECU 状態：

STATE_INIT
STATE_STANDBY
STATE_ACTIVE
STATE_ERROR

コードをコピーする

イベント例：

READY / START / STOP / RESET / FAULT

yaml
コードをコピーする

状態遷移テーブルは `state_machine.c` の先頭に記載しています。

---

## 📌 この Visual Studio 版の特徴

- Linux版と同等のロジックを保持  
- Windows環境用に `unistd.h` → 削除／置き換え済み  
- **フォルダ階層を app / driver / service に整理し、実機実装を意識した構造に改善**
- すぐに移植／拡張できるテンプレートとして利用可能

---

## 📄 ライセンス

学習用途のため特に制限なし。  
自由に改変してご利用ください。

---

## ✉ サポート

- ステートマシン拡張  
- CAN モジュール追加  
- Visual Studio の設定  
- GitHub ブランチ運用

何でも気軽にご相談ください。
