#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_P_Principal.generated.h"

UCLASS()
class GALAGA_REMASTERED_API AHUD_P_Principal : public AHUD
{
    GENERATED_BODY()

public:
    AHUD_P_Principal();

    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> WidgetPrincipalClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> MainScreenClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> LoadingScreenClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> HistoryScreenClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> OptionsMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> ControlsMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> CreditsMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> TransitionScreenClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> PauseMenuClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> MissionMessageClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> GameStartedWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> LevelScreenClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> GameOverWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> BossHealthBarWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* StartGameSound;

    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* CreditsSound;

    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class UAudioComponent* CreditsAudioComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* Intro_Principal;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> VictoryWidgetClass;

    //Para el sonido de victoria
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* VictorySound;

    // Definir el sonido del panel principal
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* MainMenuSound;

    // Definir el AudioComponent para manejar el sonido del panel principal
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class UAudioComponent* MainMenuAudioComponent;

    // Definir el sonido del panel de dificultad
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* DifficultySound;

    // Definir el AudioComponent para manejar el sonido del panel de dificultad
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class UAudioComponent* DifficultyAudioComponent;

    //para la barra de galactus

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<class UUserWidget> GalactusHealthBarWidgetClass;


    // Sonido del menú de controles
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* ControlsSound;

    // AudioComponent para manejar el sonido del menú de controles
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class UAudioComponent* ControlsAudioComponent;

    // Sonido del menú de opciones
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class USoundBase* OptionsSound;

    // AudioComponent para manejar el sonido del menú de opciones
    UPROPERTY(EditDefaultsOnly, Category = "Audio")
    class UAudioComponent* OptionsAudioComponent;



    void StartGameplayFacil();

    void StartGameplayNormal();

    void StartGameplayDificil(); 

    void ShowDifficultySelection();
    void HideDifficultySelection();



    void ShowMainMenu();
    void HideMainMenu();

    void ShowHistoryScreen();
    void ShowLoadingScreen();

    void HideLoadingScreen();

    void ShowOptionsMenu();
    void HideOptionsMenu();

    void ShowControlsMenu();
    void HideControlsMenu();

    void ShowCreditsMenu();

    void StartGameplay();

    void ShowTransitionScreen();
    void HideTransitionScreen();

    void ShowMissionMessage(const FString& MissionMessage);
    void HideMissionMessage();
    void ToggleMissionMessage();

    void ShowLevelScreen(const FString& LevelMessage);
    void HideLevelScreen();

    //Metodos para el GameStartedWidget
    void ShowGameStartedWidget();
    void HideGameStartedWidget();

    void ShowGameOverScreen();
    void RestartGameAndShowMainMenu();

    UPROPERTY(BlueprintReadOnly)
    class APF_LEVEL_DIFFICULTY_PRIM_B* LevelDifficultyManager;

public:
    UUserWidget* WidgetPrincipal;
    UUserWidget* MainScreen;
    UUserWidget* LoadingScreen;
    UUserWidget* HistoryScreen;
    UUserWidget* OptionsMenu;
    UUserWidget* ControlsMenu;
    UUserWidget* CreditsMenu;
    UUserWidget* TransitionScreen;
    UUserWidget* PauseMenu;
    UUserWidget* MissionMessageP;
    UUserWidget* GameStartedWidget;
    //UUserWidget* BossHealthBarWidget;
    UUserWidget* GameOverWidget;

    class UW_BAR_SHIP_BOSS_GGG* BossHealthBarWidget;

    class UW_Screen_Level_Iden* LevelScreenWidget;

    class UW_Screen_Message_MA* MissionMessageWidget;

    class UW_Victory_Game* VictoryWidget;

    class UWidget_Bar_Galactus* GalactusHealthBarWidget;

    FTimerHandle TimerHandle;
    int32 SelectedMode;

    void InitializeLevelDifficultyManager();

public:
    void PlayCreditsSound();
    void StopCreditsSound();

    void ShowPauseMenu();
    void HidePauseMenu();

    void ShowBossHealthBar();
    void HideBossHealthBar();

    void ShowGalactusHealthBar();
    void HideGalactusHealthBar();


    bool bIsPaused;
    FTimerHandle LevelScreenTimerHandle;
    FTimerHandle MissionMessageTimerHandle;
    FString CurrentMissionMessage;

public:

    void ShowVictoryWidget();

    void HideVictoryWidget();
};
