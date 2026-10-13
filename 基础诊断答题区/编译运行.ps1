param()
$ErrorActionPreference = 'Stop'
$toolBin = 'C:\Users\Administrator\Documents\Codex\2026-10-12\wdo\work\devdocqa-build\msys\ucrt64\bin'
$compiler = Join-Path $toolBin 'clang++.exe'
if (-not (Test-Path -LiteralPath $compiler)) { throw '本机编译器路径不存在，请告诉助手当前错误。' }
$env:PATH = $toolBin + ';' + $env:PATH
$sourceFile = Join-Path $PSScriptRoot 'A1_Buffer.cpp'
$buildDir = Join-Path $env:TEMP 'CodexBaselineA1'
New-Item -ItemType Directory -Path $buildDir -Force | Out-Null
$program = Join-Path $buildDir 'A1_Buffer.exe'
& $compiler '-std=c++17' '-stdlib=libstdc++' '-Wall' '-Wextra' '-g' $sourceFile '-o' $program
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
Write-Host '编译成功，下面运行你写的 main。空模板没有完成诊断。'
& $program
exit $LASTEXITCODE
