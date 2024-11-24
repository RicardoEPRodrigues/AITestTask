// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCoordinator.h"

#include "AITestTask/AITestTask.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardComponent.h"

// Sets default values
AEnemyCoordinator::AEnemyCoordinator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyCoordinator::BeginPlay()
{
	Super::BeginPlay();

	CurrentAttackInterval = FMath::Max(AttackInterval + AttackIntervalDeduction, 0.0f);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), EnemyCharacterClass, FoundActors);

	for (auto Actor : FoundActors)
	{
		if (AAIController* AIController = Cast<AAIController>(Actor))
		{
			FoundAIControllers.Add(AIController);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyCoordinator::CoordinateAttack, 1.0f, false, 2.0f);
}

// Called every frame
void AEnemyCoordinator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(AttackingController))
	{
		return;
	}

	UBlackboardComponent* Blackboard = AttackingController->GetBlackboardComponent();
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	
	if (Blackboard->GetValueAsBool(HasAttackedKey) && !TimerManager.IsTimerActive(TimerHandle))
	{
		CurrentAttackInterval = FMath::Max(CurrentAttackInterval - AttackIntervalDeduction, 0.0f);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyCoordinator::CoordinateAttack, 1.0f, false, CurrentAttackInterval);
		LogToConsoleAndScreen(this, FString::Printf(TEXT("Attacker has attacked. Setting delay to %f"), CurrentAttackInterval));
	}
}

void AEnemyCoordinator::CoordinateAttack()
{
	LogToConsoleAndScreen(this, FString::Printf(TEXT("Triggering Coordinated Attack!")));
	
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	
	if (IsValid(AttackingController))
	{
		// Select a new attacking controller from the rest of the poll.
		TArray<AAIController*> OtherControllers = FoundAIControllers;
		OtherControllers.Remove(AttackingController);
		AttackingController = OtherControllers[FMath::RandRange(0, OtherControllers.Num() - 1)];
	} else
	{
		// Select random attacking controller.
		AttackingController = FoundAIControllers[FMath::RandRange(0, FoundAIControllers.Num() - 1)];
	}

	if (!IsValid(AttackingController))
	{
		UE_LOG(LogAiTest, Warning, TEXT("No valid attacking controller found."));
		return;
	}

	for (auto AIController : FoundAIControllers)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		Blackboard->SetValueAsBool(IsAttackingKey, AIController == AttackingController);
	}
	LogToConsoleAndScreen(this, FString::Printf(TEXT("Attacker is %s"), *GetNameSafe(AttackingController)));
}
