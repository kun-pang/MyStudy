# 将文件从GBK/GB2312编码转换为UTF-8编码的PowerShell脚本

# 要转换的文件路径
$files = @(
    "e:\QTProject\Thread Pool\CPP\threadPoolCPP\ThreadPool.h",
    "e:\QTProject\Thread Pool\CPP\threadPoolCPP\TaskQueue.h"
)

foreach ($file in $files) {
    # 读取文件内容（以GB2312编码）
    $content = Get-Content -Path $file -Encoding Default -Raw
    
    # 创建备份文件
    $backupFile = "$file.bak"
    Copy-Item -Path $file -Destination $backupFile -Force
    Write-Host "已创建备份文件: $backupFile"
    
    # 以UTF-8编码写入文件
    $utf8NoBom = New-Object System.Text.UTF8Encoding $false
    [System.IO.File]::WriteAllText($file, $content, $utf8NoBom)
    Write-Host "已将文件 $file 转换为UTF-8编码（无BOM）"
}

Write-Host "转换完成！请检查文件中的中文注释是否正确显示。"