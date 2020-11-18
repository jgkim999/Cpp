# C++ example

* [Visual studio 2019](https://visualstudio.microsoft.com)
* [Tbb](https://github.com/01org/tbb)
* [boost](https://github.com/boostorg)

## Vcpkg 서버 모듈 초기화

https://github.com/microsoft/vcpkg

```powershell
git submodule init
```

## Vcpkg 서버 모듈 update

```powershell
git submodule update
```
또는
```powershell
git submodule update --init --recursive
git submodule foreach --recursive git fetch
git submodule foreach git merge origin master
```

## Vcpkg 폴더로 이동

```powershell
cd vcpkg
```

## Vcpkg 빌드

```powershell
bootstrap-vcpkg.bat
```

## boost 설치

```powershell
vcpkg install boost:x64-windows
```

|             |                                              |
|-------------|----------------------------------------------|
| include     | .\vcpkg\installed\x64-windows\include\boost\ |
| Release lib | .\vcpkg\installed\x64-windows\lib\           |
| Release dll | .\vcpkg\installed\x64-windows\bin\           |
| Debug lib   | .\vcpkg\installed\x64-windows\debug\lib\     |
| Debug dll   | .\vcpkg\installed\x64-windows\debug\bin\     |

## tbb 설치

```powershell
vcpkg install tbb:x64-windows
```

|             |                                              |
|-------------|----------------------------------------------|
| include     | .\vcpkg\installed\x64-windows\include\tbb\   |
| Release lib | .\vcpkg\installed\x64-windows\lib\           |
| Release dll | .\vcpkg\installed\x64-windows\bin\           |
| Debug lib   | .\vcpkg\installed\x64-windows\debug\lib\     |
| Debug dll   | .\vcpkg\installed\x64-windows\debug\bin\     |
