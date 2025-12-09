# CAN State Machine Sample (C Language)

CAN通信を模擬した入力イベントにより、ECUの状態遷移を行う  
**状態遷移ステートマシンのサンプル実装（C言語）**です。

車載・組込み系開発を想定し、  
「CAN受信 → イベントバッファ → 状態遷移 → 状態出力」
という実務に近い構成で実装しています。

---

## ■ 機能概要

- CANフレームのテーブル照合
- 受信イベントのバリデーション
- 割り込み風のイベント投入
- イベントバッファによる非同期処理
- テーブル駆動型 状態遷移ステートマシン
- 不正遷移・異常イベントの検出とログ出力

---

## ■ 状態一覧（ECU State）

| 状態 | 説明 |
|------|------|
| INIT | 初期化 |
| STANDBY | 待機 |
| ACTIVE | 稼働中 |
| ERROR | 異常状態 |

---

## ■ CAN イベント一覧

| イベント | 入力 | 内容 |
|----------|------|------|
| READY    | r    | 起動準備 |
| START    | s    | 動作開始 |
| STOP     | t    | 停止 |
| RESET    | x    | リセット |
| FAULT    | e    | エラー |

---

## ■ 状態遷移表

| 現在状態 | イベント | 次状態 |
|----------|----------|--------|
| INIT     | READY    | STANDBY |
| STANDBY  | START    | ACTIVE |
| ACTIVE   | STOP     | STANDBY |
| STANDBY  | FAULT    | ERROR |
| ACTIVE   | FAULT    | ERROR |
| ERROR    | RESET    | INIT |
| STANDBY  | RESET    | INIT |
| ACTIVE   | RESET    | INIT |

上記以外の組み合わせは **すべて不正遷移としてエラーログ出力のみ**行います。

---

## ■ ファイル構成

lesson3/
├─ can.c // CAN フレーム処理
├─ can.h
├─ event_buffer.c // イベントバッファ
├─ event_buffer.h
├─ state_machine.c // 状態遷移処理
├─ state_machine.h
├─ main.c // メインループ
└─ README.md


---

## ■ 動作概要

1. `main()` でキー入力取得
2. `Can_RxInterruptMock()` で擬似割り込み生成
3. `CheckCanFrame()` でCANイベント判定
4. `EventBuffer_Push()` でイベント格納
5. メインループで `EventBuffer_Pop()`
6. `StateMachine_UpdateByEvent()` により状態遷移
7. `PrintState()` により現在状態を出力

---

## ■ ビルド方法

```bash
gcc can.c event_buffer.c state_machine.c main.c -o lesson3
■ 実行方法
bash
コードをコピーする
./lesson3
■ 操作方法
キー	動作
r	READY
s	START
t	STOP
e	FAULT
x	RESET
q	終了

■ 実行例
powershell
コードをコピーする
r → 状態 : 待機
s → 状態 : 稼働中
e → 状態 : エラー
x → 状態 : 初期化
■ 設計上の工夫点
テーブル駆動による状態遷移（if/switch 非依存）

CAN入力のバリデーション処理を分離

割り込みとメインループの責務分離

不正遷移は状態を変更しないフェールセーフ設計

将来的なRTOS / マルチタスク化を想定した構造

■ 今後の拡張予定
イベントバッファのリングバッファ化

スレッドセーフ化（mutex対応）

ログ出力インタフェース分離

単体テストコードの追加

AUTOSAR風API構造への拡張

■ 開発環境
OS: Ubuntu

Compiler: gcc

Language: C (C99準拠)

■ ライセンス
MIT License（予定）
