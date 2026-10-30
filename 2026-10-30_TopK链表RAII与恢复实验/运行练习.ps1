param([string]$SourceFile = '01_TopK完整复测.cpp')
$ErrorActionPreference = 'Stop'
$taskWorkspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '../../../..'))
$taskSource = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot $SourceFile))
if (([IO.Path]::GetDirectoryName($taskSource)) -ne $PSScriptRoot -or [IO.Path]::GetExtension($taskSource) -ne '.cpp') {
    throw 'Choose a C++ exercise in the current daily folder.'
}
$taskCompilerBin = Join-Path $taskWorkspace 'work/devdocqa-build/msys/ucrt64/bin'
$taskCompiler = Join-Path $taskCompilerBin 'g++.exe'
if (-not (Test-Path -LiteralPath $taskCompiler)) { throw 'Prepared GCC compiler not found.' }
$taskBuild = Join-Path $taskWorkspace 'work/interview-pack-check/2026-10-30'
New-Item -ItemType Directory -Path $taskBuild -Force | Out-Null
$taskCpp = Join-Path $taskBuild 'exercise.cpp'
$taskExe = Join-Path $taskBuild 'exercise.exe'
Copy-Item -LiteralPath $taskSource -Destination $taskCpp -Force
$taskOldPath = $env:PATH
try {
    $env:PATH = $taskCompilerBin + ';' + $env:PATH
    & $taskCompiler -std=c++17 -Wall -Wextra -pedantic $taskCpp -o $taskExe
    if ($LASTEXITCODE -ne 0) { throw 'Compilation failed.' }
    & $taskExe
    if ($LASTEXITCODE -ne 0) { throw 'Exercise is incomplete or tests failed.' }
} finally {
    $env:PATH = $taskOldPath
}
