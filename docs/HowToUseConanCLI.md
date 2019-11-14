# Conan CLI

## Overview
- 01. Build Library (install dependency)
- 02. 

### 01. Build Library

#### ConanFile.txt
- 學會了基本寫法
- 放 cmake 跟 主要使用 IDE

#### Conan CLI (build) 開發中。

- 安裝相依“包"
- 根據Cmake 產生 Xcode IDE專案檔
- 產生相依圖 deps.html

```
conan install .. --build=missing
cmake .. -G "Xcode"
cmake --build .
conan info .. --graph deps.html
```
- PS: cmake --build . --config Release
- PS: cmake --build . --config Debug

#### Conan CLI (config)
```
conan config get log.level
conan config home
```

#### 查看目前的 info
```
conan info .
```

#### Conan CLI 發布(在root)
```
conan install . -if build_x86 -s arch=x86
conan build . -bf build_x86
```

### 02. New Pacakge (for this library)

#### CLI
```
conan new geo_object/1.1 -t
```
