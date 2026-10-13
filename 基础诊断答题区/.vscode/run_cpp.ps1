param([Parameter(Mandatory=$true)][string]$SourceFile, [switch]$CompileOnly)
$ErrorActionPreference = 'Stop'
[Console]::OutputEncoding = New-Object System.Text.UTF8Encoding($false)
$toolBin = 'C:\Users\Administrator\Documents\Codex\2026-10-12\wdo\work\devdocqa-build\msys\ucrt64\bin'
$compiler = Join-Path $toolBin 'clang++.exe'
if (-not (Test-Path -LiteralPath $compiler)) { throw '找不到C++编译器，请联系助手修正路径。' }
if (-not (Test-Path -LiteralPath $SourceFile)) { throw '请先保存当前C++文件，再运行。' }
if ([IO.Path]::GetExtension($SourceFile) -notin @('.cpp','.cc','.cxx')) { throw '请切换到一个C++源文件，再按Ctrl+Shift+B。' }
$env:PATH = $toolBin + ';' + $env:PATH
# 链接器在中文输出路径下可能报错，生成程序统一放在临时目录。
$buildDir = Join-Path $env:TEMP 'CodexCppPractice'
New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
$program = Join-Path $buildDir 'practice.exe'
# Windows链接器会把中文源文件名用于临时目标文件；先复制成ASCII文件名。
$compileSource = Join-Path $buildDir 'practice_source.cpp'
Copy-Item -LiteralPath $SourceFile -Destination $compileSource -Force
Write-Host ('正在编译：' + $SourceFile)
& $compiler '-std=c++17' '-stdlib=libstdc++' '-Wall' '-Wextra' '-g' $compileSource '-o' $program
if ($LASTEXITCODE -ne 0) { Write-Host '编译未通过，请查看上面的错误与行号。'; exit $LASTEXITCODE }
if ($CompileOnly) { Write-Host '编译成功，交给调试器运行。'; exit 0 }
Write-Host '编译成功，运行结果：'
& $program
exit $LASTEXITCODE
