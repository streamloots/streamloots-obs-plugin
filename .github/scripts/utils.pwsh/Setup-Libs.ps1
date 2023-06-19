function Setup-Libs {
    if ( ! ( Test-Path function:Log-Output ) ) {
        . $PSScriptRoot/Logger.ps1
    }

    if ( ! ( Test-Path function:Check-Git ) ) {
        . $PSScriptRoot/Check-Git.ps1
    }

    Check-Git

    if ( ! ( Test-Path function:Ensure-Location ) ) {
        . $PSScriptRoot/Ensure-Location.ps1
    }

    if ( ! ( Test-Path function:Invoke-GitCheckout ) ) {
        . $PSScriptRoot/Invoke-GitCheckout.ps1
    }

    Log-Information 'Setting up websokketpp...'

    $WebsocketppVersion = $BuildSpec.dependencies.'websocketpp'.version
    $WebsocketppRepository = $BuildSpec.dependencies.'websocketpp'.repository
    $WebsocketppBranch = $BuildSpec.dependencies.'websocketpp'.branch    
    $WebsocketppHash = $BuildSpec.dependencies.'websocketpp'.hash

    if ( $WebsocketppVersion -eq '' ) {
        throw 'No websocketpp version found in buildspec.json.'
    }

    Push-Location -Stack BuildTemp
    Ensure-Location -Path "$(Resolve-Path -Path "${ProjectRoot}/../")/websocketpp"

    if ( ! ( ( $script:SkipAll ) -or ( $script:SkipUnpack ) ) ) {
        Invoke-GitCheckout -Uri $WebsocketppRepository -Commit $WebsocketppHash -Path . -Branch $WebsocketppBranch
    }

    Pop-Location -Stack BuildTemp

    Log-Information 'Setting up asio...'

    $AsioVersion = $BuildSpec.dependencies.'asio'.version
    $AsioRepository = $BuildSpec.dependencies.'asio'.repository
    $AsioBranch = $BuildSpec.dependencies.'asio'.branch    
    $AsioHash = $BuildSpec.dependencies.'asio'.hash

    if ( $AsioVersion -eq '' ) {
        throw 'No asio version found in buildspec.json.'
    }

    Push-Location -Stack BuildTemp
    Ensure-Location -Path "$(Resolve-Path -Path "${ProjectRoot}/../")/asio"

    if ( ! ( ( $script:SkipAll ) -or ( $script:SkipUnpack ) ) ) {
        Invoke-GitCheckout -Uri $AsioRepository -Commit $AsioHash -Path . -Branch $AsioBranch
    }

    Pop-Location -Stack BuildTemp
}
