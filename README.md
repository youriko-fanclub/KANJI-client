# KANJI
- OpenSiv3D v0.4.3 Game Project Template

漢字発見!モジバトル

## QuickStart
```
$ make init
$ make run
```

## Build on CLI
### Default build
```
$ make build
```

### Debug build
```
$ make build/debug
```

### Release Build
```
$ make build/release
```


## Coding Conventions
```
- case
  - variable: snake_case
  - function: camelCase
  - class: PascalCase
  - namespace: smallcase
  - enum: PascalCase
  - macro: CAPITAL_SNAKE
- prefix
  - class member field: m_
  - class static member field: s_
- indent
  - default: 4
  - namespace: 0
```


## Sceneの追加手順

1. XXXXScene.hpp / cpp を追加、class XXXXScene : public KanjiScene
1. Scenes.hpp にincludeを追加
1. SceneStates.hpp の enum State に XXXX を追加
1. SequenseManager::initialize() に遷移方法を設定

