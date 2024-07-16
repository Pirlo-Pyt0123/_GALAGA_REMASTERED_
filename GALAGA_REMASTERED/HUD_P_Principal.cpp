


#include "HUD_P_Principal.h"
#include "Blueprint/UserWidget.h"
#include "W_Main_screen.h"
#include "Widget_Principal.h"
#include "W_Histoy_Beginning.h"
#include "PF_LEVEL_DIFFICULTY_PRIM_B.h"
#include "Kismet/GameplayStatics.h"
#include "W_One_Charging.h"
#include "W_Controler_Ma.h"
#include "W_Creditos_MP.h"
#include "W_Transition_CP.h"
#include "W_Menu_Pause_MP.h"
#include "W_Screen_Message_MA.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "W_PDD_Game_Started.h"
#include "W_Screen_Level_Iden.h"
#include "W_Game_Over_MA.h"
#include "W_BAR_SHIP_BOSS_GGG.h"
#include "W_Victory_Game.h"
#include "Widget_Bar_Galactus.h"

AHUD_P_Principal::AHUD_P_Principal()
{

    static ConstructorHelpers::FClassFinder<UUserWidget> MainScreenWidgetClass(TEXT("/Game/Widged/W_Main_Menu_P"));
    if (MainScreenWidgetClass.Succeeded())
    {
        MainScreenClass = MainScreenWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Widged/Interfaz_Grafica"));
    if (WidgetClass.Succeeded())
    {
        WidgetPrincipalClass = WidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> LoadingScreenWidgetClass(TEXT("/Game/Widged/One_Charging"));
    if (LoadingScreenWidgetClass.Succeeded())
    {
        LoadingScreenClass = LoadingScreenWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> HistoryScreenWidgetClass(TEXT("/Game/Widged/P_History_MS"));
    if (HistoryScreenWidgetClass.Succeeded())
    {
        HistoryScreenClass = HistoryScreenWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> OptionsMenuWidgetClass(TEXT("/Game/Widged/Screen_MA_Options_"));
    if (OptionsMenuWidgetClass.Succeeded())
    {
        OptionsMenuClass = OptionsMenuWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> ControlsMenuWidgetClass(TEXT("/Game/Widged/Screen_Controls"));
    if (ControlsMenuWidgetClass.Succeeded())
    {
        ControlsMenuClass = ControlsMenuWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> CreditsMenuWidgetClass(TEXT("/Game/Widged/CREDITOS_PB"));
    if (CreditsMenuWidgetClass.Succeeded())
    {
        CreditsMenuClass = CreditsMenuWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> TransitionScreenWidgetClass(TEXT("/Game/Widged/Screen_Transition"));
    if (TransitionScreenWidgetClass.Succeeded())
    {
        TransitionScreenClass = TransitionScreenWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> PauseMenuWidgetClass(TEXT("/Game/Widged/Screen_Pause"));
    if (PauseMenuWidgetClass.Succeeded())
    {
        PauseMenuClass = PauseMenuWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> MissionMessageWidgetClassFinder(TEXT("/Game/Widged/Screen_Message"));
    if (MissionMessageWidgetClassFinder.Succeeded())
    {
        MissionMessageClass = MissionMessageWidgetClassFinder.Class;
    }

    MissionMessageP = nullptr; 

    static ConstructorHelpers::FClassFinder<UUserWidget> GameStartedWidgetClassFFF(TEXT("/Game/Widged/Screen_Game_ON"));
    if (GameStartedWidgetClassFFF.Succeeded())
    {
        GameStartedWidgetClass = GameStartedWidgetClassFFF.Class;
    }

    GameStartedWidget = nullptr;

    static ConstructorHelpers::FClassFinder<UUserWidget> LevelScreenWidgetClass(TEXT("/Game/Widged/Screen_MS_Pat"));
    if (LevelScreenWidgetClass.Succeeded())
    {
        LevelScreenClass = LevelScreenWidgetClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> GameOverWidgetClassFinder(TEXT("/Game/Widged/Game_Over"));
    if (GameOverWidgetClassFinder.Succeeded())
    {
        GameOverWidgetClass = GameOverWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FObjectFinder<USoundBase> StartGameSoundObject(TEXT("/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Comienzo_Epic.Comienzo_Epic"));
    if (StartGameSoundObject.Succeeded())
    {
        StartGameSound = StartGameSoundObject.Object;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> BossHealthBarWidgetClassFinder(TEXT("/Game/Widged/Screen_Space_Bosses_Bar"));
    if (BossHealthBarWidgetClassFinder.Succeeded())
    {
        BossHealthBarWidgetClass = BossHealthBarWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> GalactusHealthBarWidgetClassfinder(TEXT("/Game/Widged/Screen_Bar_Galactus"));
    if (GalactusHealthBarWidgetClassfinder.Succeeded())
    {
        GalactusHealthBarWidgetClass = GalactusHealthBarWidgetClassfinder.Class;
    }


    static ConstructorHelpers::FObjectFinder<USoundBase> CreditsSoundObject(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/Hiper_Creditos.Hiper_Creditos'"));
    if (CreditsSoundObject.Succeeded())
    {
        CreditsSound = CreditsSoundObject.Object;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> VictoryWidgetBPClass(TEXT("/Game/Widged/Screen_Victory"));
    if (VictoryWidgetBPClass.Succeeded())
    {
        VictoryWidgetClass = VictoryWidgetBPClass.Class;
    }


    static ConstructorHelpers::FObjectFinder<USoundBase> VictorySoundObject(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/victory.victory'"));
    if (VictorySoundObject.Succeeded())
	{
		VictorySound = VictorySoundObject.Object;
	}

    static ConstructorHelpers::FObjectFinder<USoundBase> MainMenuSoundObject(TEXT("/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/ENTRADA_EPIC_MAIN_MENU.ENTRADA_EPIC_MAIN_MENU"));
    if (MainMenuSoundObject.Succeeded())
    {
        MainMenuSound = MainMenuSoundObject.Object;
    }


    // Inicializar el sonido del panel de dificultad
    static ConstructorHelpers::FObjectFinder<USoundBase> DifficultySoundObject(TEXT("SoundWave'/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/DIFFICULT_SOUND.DIFFICULT_SOUND'"));
    if (DifficultySoundObject.Succeeded())
    {
        DifficultySound = DifficultySoundObject.Object;
    }



    static ConstructorHelpers::FObjectFinder<USoundBase> ControlsSoundObject(TEXT("/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/CONTROL_SOUND.CONTROL_SOUND"));
    if (ControlsSoundObject.Succeeded())
    {
        ControlsSound = ControlsSoundObject.Object;
    }


    //PARA EL SONIDO DE OPTIONS
    static ConstructorHelpers::FObjectFinder<USoundBase> OptionsSoundObject(TEXT("/Game/Audio_Unreal_Engine/GALAGA_SOUND_MUSIC/OPTIONS_SOUND.OPTIONS_SOUND"));
    if (OptionsSoundObject.Succeeded())
    {
        OptionsSound = OptionsSoundObject.Object;
    }

    // Inicializar el AudioComponent del menú de opciones
    OptionsAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("OptionsAudioComponent"));
    OptionsAudioComponent->bAutoActivate = false; // No activar automáticamente
    OptionsAudioComponent->SetupAttachment(RootComponent);




    // Inicializar el AudioComponent del menú de controles
    ControlsAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ControlsAudioComponent"));
    ControlsAudioComponent->bAutoActivate = false; // No activar automáticamente
    ControlsAudioComponent->SetupAttachment(RootComponent);




    // Inicializar el AudioComponent del panel de dificultad
    DifficultyAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("DifficultyAudioComponent"));
    DifficultyAudioComponent->bAutoActivate = false; 
    DifficultyAudioComponent->SetupAttachment(RootComponent);



    // Inicializar el AudioComponent del panel principal
    MainMenuAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MainMenuAudioComponent"));
    MainMenuAudioComponent->bAutoActivate = false; 
    MainMenuAudioComponent->SetupAttachment(RootComponent);



    CreditsAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("CreditsAudioComponent"));
    CreditsAudioComponent->bAutoActivate = false; 
    CreditsAudioComponent->SetupAttachment(RootComponent);
}

void AHUD_P_Principal::BeginPlay()
{
    Super::BeginPlay();
    ShowMainMenu();

    if (LevelScreenClass)
    {
        LevelScreenWidget = CreateWidget<UW_Screen_Level_Iden>(GetWorld(), LevelScreenClass);
    }

    if (MissionMessageClass)
    {
        MissionMessageWidget = CreateWidget<UW_Screen_Message_MA>(GetWorld(), MissionMessageClass);
    }

}

void AHUD_P_Principal::ShowGameOverScreen()
{
    if (GameOverWidgetClass)
    {
        GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
        if (GameOverWidget)
        {
            HideGameStartedWidget();
            GameOverWidget->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(GameOverWidget->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }
        }
    }
}

void AHUD_P_Principal::RestartGameAndShowMainMenu()
{
    //// Reiniciar el juego
    //UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

    // Mostrar el menú principal
    if (MainScreenClass)
    {
        GameStartedWidget = CreateWidget<UUserWidget>(GetWorld(), MainScreenClass);
        if (GameStartedWidget)
        {
            GameStartedWidget->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(MainScreen->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }
        }
    }
}


void AHUD_P_Principal::ShowGameStartedWidget()
{
    if (GameStartedWidgetClass)
    {
        GameStartedWidget = CreateWidget<UUserWidget>(GetWorld(), GameStartedWidgetClass);
        if (GameStartedWidget)
        {
            GameStartedWidget->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(GameStartedWidget->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }
        }
    }
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create GameStartedWidget"));
	}
}

void AHUD_P_Principal::HideGameStartedWidget()
{
    if (GameStartedWidget)
    {
        GameStartedWidget->RemoveFromParent();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameStartedWidget is not initialized"));
    }
}



void AHUD_P_Principal::ShowVictoryWidget()
{
    if (VictoryWidgetClass != nullptr)
    {
        VictoryWidget = CreateWidget<UW_Victory_Game>(GetWorld(), VictoryWidgetClass);
        if (VictoryWidget != nullptr)
        {
            VictoryWidget->AddToViewport();
        }
    }

    if (VictorySound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), VictorySound);
	}

    // Programar la ocultación del widget después de 8 segundos y abrir los créditos
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
        {
            HideVictoryWidget();
            ShowCreditsMenu();
        }, 8.0f, false);
}

void AHUD_P_Principal::HideVictoryWidget()
{
    if (VictoryWidget != nullptr)
    {
        VictoryWidget->RemoveFromViewport();
    }
}



void AHUD_P_Principal::ShowLevelScreen(const FString& LevelMessage)
{
    if (LevelScreenWidget && LevelScreenWidget->IsInViewport())
    {
        LevelScreenWidget->RemoveFromParent();
    }

    if (!LevelScreenWidget)
    {
        LevelScreenWidget = CreateWidget<UW_Screen_Level_Iden>(GetWorld(), LevelScreenClass);
    }

    if (LevelScreenWidget)
    {
        LevelScreenWidget->AddToViewport();
        LevelScreenWidget->SetLevelMessage(LevelMessage);
        LevelScreenWidget->StartMove();

        GetWorld()->GetTimerManager().SetTimer(LevelScreenTimerHandle, this, &AHUD_P_Principal::HideLevelScreen, 6.0f, false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create or initialize LevelScreenWidget"));
    }
}

void AHUD_P_Principal::HideLevelScreen()
{
    if (LevelScreenWidget)
    {
        LevelScreenWidget->RemoveFromParent();
        LevelScreenWidget = nullptr;  // Ensure the widget is reset
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("LevelScreenWidget is not initialized"));
    }
}


void AHUD_P_Principal::ShowPauseMenu()
{
    if (PauseMenuClass)
    {
        PauseMenu = CreateWidget<UUserWidget>(GetWorld(), PauseMenuClass);
        if (PauseMenu)
        {
            PauseMenu->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(PauseMenu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            UGameplayStatics::SetGamePaused(GetWorld(), true);
            bIsPaused = true;
        }
    }
}

void AHUD_P_Principal::HidePauseMenu()
{
    if (PauseMenu)
    {
        PauseMenu->RemoveFromParent();
        PauseMenu = nullptr;

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            //PlayerController->bShowMouseCursor = false;
            //PlayerController->bEnableClickEvents = false;
            //PlayerController->bEnableMouseOverEvents = false;
            FInputModeGameOnly InputMode;
            PlayerController->SetInputMode(InputMode);
        }

        UGameplayStatics::SetGamePaused(GetWorld(), false);
        bIsPaused = false;
    }
}

void AHUD_P_Principal::ShowBossHealthBar()
{
    if (BossHealthBarWidgetClass)
    {
        BossHealthBarWidget = CreateWidget<UW_BAR_SHIP_BOSS_GGG>(GetWorld(), BossHealthBarWidgetClass);
        if (BossHealthBarWidget)
        {
            BossHealthBarWidget->AddToViewport();
        }
    }
}

void AHUD_P_Principal::HideBossHealthBar()
{
    if (BossHealthBarWidget)
    {
        BossHealthBarWidget->RemoveFromParent();
        BossHealthBarWidget = nullptr;
    }
}

void AHUD_P_Principal::ShowGalactusHealthBar()
{
    if (GalactusHealthBarWidgetClass)
	{
		GalactusHealthBarWidget = CreateWidget<UWidget_Bar_Galactus>(GetWorld(), GalactusHealthBarWidgetClass);
		if (GalactusHealthBarWidget)
		{
			GalactusHealthBarWidget->AddToViewport();
		}
	}
}

void AHUD_P_Principal::HideGalactusHealthBar()
{
    if (GalactusHealthBarWidget)
	{
		GalactusHealthBarWidget->RemoveFromParent();
		GalactusHealthBarWidget = nullptr;
	}
}

void AHUD_P_Principal::ShowMainMenu()
{
    if (MainScreenClass)
    {
        MainScreen = CreateWidget<UUserWidget>(GetWorld(), MainScreenClass);
        if (MainScreen)
        {
            MainScreen->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(MainScreen->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            if (MainMenuSound && MainMenuAudioComponent)
            {
                MainMenuAudioComponent->SetSound(MainMenuSound);
                MainMenuAudioComponent->Play();
            }

            InitializeLevelDifficultyManager();
        }
    }
}

void AHUD_P_Principal::HideMainMenu()
{
    if (MainScreen)
    {
        MainScreen->RemoveFromParent();
        MainScreen = nullptr;

        // Detener el sonido del menú principal
        if (MainMenuAudioComponent)
        {
            MainMenuAudioComponent->Stop();
        }
    }
}

void AHUD_P_Principal::ShowDifficultySelection()
{
    if (WidgetPrincipalClass)
    {
        HideMainMenu();

        WidgetPrincipal = CreateWidget<UUserWidget>(GetWorld(), WidgetPrincipalClass);
        if (WidgetPrincipal)
        {
            WidgetPrincipal->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(WidgetPrincipal->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            // Reproducir el sonido del menú principal
            if (DifficultySound && DifficultyAudioComponent)
            {
                DifficultyAudioComponent->SetSound(DifficultySound);
                DifficultyAudioComponent->Play();
            }

            if (WidgetPrincipal)
            {
                UWidget_Principal* Widget = Cast<UWidget_Principal>(WidgetPrincipal);
                if (Widget)
                {
                    Widget->LevelDifficultyManager = LevelDifficultyManager;
                }
            }
        }
    }
}

void AHUD_P_Principal::HideDifficultySelection()
{
    if (WidgetPrincipal)
	{
		WidgetPrincipal->RemoveFromParent();
		WidgetPrincipal = nullptr;

        // Detener el sonido del panel de dificultad
        if (DifficultyAudioComponent)
        {
            DifficultyAudioComponent->Stop();
        }
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetPrincipal is not initialized"));
	}
}

void AHUD_P_Principal::ShowLoadingScreen()
{
    HideDifficultySelection();

    if (LoadingScreenClass)
    {
        LoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenClass);
        if (LoadingScreen)
        {
            LoadingScreen->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = false;
                PlayerController->bEnableClickEvents = false;
                PlayerController->bEnableMouseOverEvents = false;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(LoadingScreen->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }
        }
    }
}

void AHUD_P_Principal::HideLoadingScreen()
{
    if (LoadingScreen)
    {
        LoadingScreen->RemoveFromParent();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("LoadingScreen is not initialized"));
    }

}

void AHUD_P_Principal::ShowHistoryScreen()
{
    if (LoadingScreen)
    {
        LoadingScreen->RemoveFromParent();
    }

    if (HistoryScreenClass)
    {
        HistoryScreen = CreateWidget<UUserWidget>(GetWorld(), HistoryScreenClass);
        if (HistoryScreen)
        {
            HistoryScreen->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(HistoryScreen->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }
        }
    }
}

void AHUD_P_Principal::ShowOptionsMenu()
{
    if (OptionsMenuClass)
    {
        HideMainMenu();

        OptionsMenu = CreateWidget<UUserWidget>(GetWorld(), OptionsMenuClass);
        if (OptionsMenu)
        {
            OptionsMenu->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(OptionsMenu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            // Reproducir el sonido del menú de opciones
            if (OptionsSound && OptionsAudioComponent)
            {
                OptionsAudioComponent->SetSound(OptionsSound);
                OptionsAudioComponent->Play();
            }
        }
    }
}

void AHUD_P_Principal::HideOptionsMenu()
{
    if (OptionsMenu)
	{
		OptionsMenu->RemoveFromParent();
		OptionsMenu = nullptr;

		if (OptionsAudioComponent)
		{
			OptionsAudioComponent->Stop();
		}
	}
}

void AHUD_P_Principal::ShowControlsMenu()
{
    if (ControlsMenuClass)
    {
        HideMainMenu();

        ControlsMenu = CreateWidget<UUserWidget>(GetWorld(), ControlsMenuClass);
        if (ControlsMenu)
        {
            ControlsMenu->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(ControlsMenu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            if (ControlsSound && ControlsAudioComponent)
            {
                ControlsAudioComponent->SetSound(ControlsSound);
                ControlsAudioComponent->Play();
            }
        }
    }
}

void AHUD_P_Principal::HideControlsMenu()
{
    if (PauseMenu && PauseMenu->IsInViewport())
    {
        if (ControlsMenu)
        {
            ControlsMenu->RemoveFromParent();
            ControlsMenu = nullptr;

            if (ControlsAudioComponent)
            {
                ControlsAudioComponent->Stop();
            }
        }
    }
    else 
    {
        ShowMainMenu();
        if (ControlsMenu)
		{
			ControlsMenu->RemoveFromParent();
			ControlsMenu = nullptr;

			if (ControlsAudioComponent)
			{
				ControlsAudioComponent->Stop();
			}
		}
	
    }


}

void AHUD_P_Principal::ShowCreditsMenu()
{
    if (CreditsMenuClass)
    {
        HideMainMenu();

        CreditsMenu = CreateWidget<UUserWidget>(GetWorld(), CreditsMenuClass);
        if (CreditsMenu)
        {
            CreditsMenu->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = true;
                PlayerController->bEnableClickEvents = true;
                PlayerController->bEnableMouseOverEvents = true;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(CreditsMenu->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }
            PlayCreditsSound();

        }
    }
}

void AHUD_P_Principal::ShowTransitionScreen()
{
    if (TransitionScreenClass)
    {
        TransitionScreen = CreateWidget<UUserWidget>(GetWorld(), TransitionScreenClass);
        if (TransitionScreen)
        {
            TransitionScreen->AddToViewport();

            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
            if (PlayerController)
            {
                PlayerController->bShowMouseCursor = false;
                PlayerController->bEnableClickEvents = false;
                PlayerController->bEnableMouseOverEvents = false;

                FInputModeUIOnly InputMode;
                InputMode.SetWidgetToFocus(TransitionScreen->TakeWidget());
                InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
                PlayerController->SetInputMode(InputMode);
            }

            UW_Transition_CP* TransitionWidget = Cast<UW_Transition_CP>(TransitionScreen);
            if (TransitionWidget)
            {
                TransitionWidget->StartTransition();
            }
        }
    }

}


void AHUD_P_Principal::HideTransitionScreen()
{
    if (TransitionScreen)
    {
        TransitionScreen->RemoveFromParent();
        TransitionScreen = nullptr;
    }

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
        PlayerController->bShowMouseCursor = true;
    }
}




void AHUD_P_Principal::InitializeLevelDifficultyManager()
{
    LevelDifficultyManager = GetWorld()->SpawnActor<APF_LEVEL_DIFFICULTY_PRIM_B>();
    if (!LevelDifficultyManager)
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to spawn LevelDifficultyManager"));
    }
}

void AHUD_P_Principal::PlayCreditsSound()
{
    if (CreditsSound && CreditsAudioComponent)
    {
        CreditsAudioComponent->SetSound(CreditsSound);
        CreditsAudioComponent->Play();
    }
}

void AHUD_P_Principal::StopCreditsSound()
{
    if (CreditsAudioComponent)
    {
        CreditsAudioComponent->Stop();
    }
}

void AHUD_P_Principal::StartGameplayFacil()
{
    SelectedMode = 0;
    ShowLoadingScreen();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHUD_P_Principal::ShowHistoryScreen, 5.0f, false);
}

void AHUD_P_Principal::StartGameplayNormal()
{
    SelectedMode = 1;
    ShowLoadingScreen();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHUD_P_Principal::ShowHistoryScreen, 5.0f, false);
}

void AHUD_P_Principal::StartGameplayDificil()
{
    SelectedMode = 2;
    ShowLoadingScreen();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AHUD_P_Principal::ShowHistoryScreen, 5.0f, false);
}

void AHUD_P_Principal::StartGameplay()
{
    if (HistoryScreen)
    {
        HistoryScreen->RemoveFromParent();
        HideLoadingScreen();
        HistoryScreen = nullptr;
    }

    LoadingScreen->AddToViewport();
    if (StartGameSound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
    }

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
        {
            HideLoadingScreen();

            if (LevelDifficultyManager)
            {
                switch (SelectedMode)
                {
                case 0:
                    LevelDifficultyManager->Activation_Mode_Easy();
                    break;
                case 1:
                    LevelDifficultyManager->Activation_Mode_Normal();
                    break;
                case 2:
                    LevelDifficultyManager->Activation_Mode_Extreme();
                    break;
                }

                ShowGameStartedWidget();

                APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
                if (PlayerController)
                {
                    FInputModeGameOnly InputMode;
                    PlayerController->SetInputMode(InputMode);
                    PlayerController->bShowMouseCursor = true;
                }
            }


        }, 8.0f, false);
}



void AHUD_P_Principal::ShowMissionMessage(const FString& MissionMessage)
{
    if (MissionMessageWidget && MissionMessageWidget->IsInViewport())
    {
        MissionMessageWidget->RemoveFromParent();
    }

    if (!MissionMessageWidget)
    {
        MissionMessageWidget = CreateWidget<UW_Screen_Message_MA>(GetWorld(), MissionMessageClass);
    }

    if (MissionMessageWidget)
    {
        MissionMessageWidget->AddToViewport();
        CurrentMissionMessage = MissionMessage;
        MissionMessageWidget->SetMissionMessage(MissionMessage);

  

        // Set a timer to hide the mission message after 5 seconds
        GetWorld()->GetTimerManager().SetTimer(MissionMessageTimerHandle, this, &AHUD_P_Principal::HideMissionMessage, 5.0f, false);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create or initialize MissionMessageWidget"));
    }
}

void AHUD_P_Principal::ToggleMissionMessage()
{
    if (MissionMessageWidget )
    {
        HideMissionMessage();
    }
    else
    {
        ShowMissionMessage(FString(CurrentMissionMessage)); // You can customize the message here
    }
}

void AHUD_P_Principal::HideMissionMessage()
{
    if (MissionMessageWidget)
    {
        MissionMessageWidget->RemoveFromParent();
        MissionMessageWidget = nullptr;  // Ensure the widget is reset
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("MissionMessageWidget is not initialized"));
    }
}
