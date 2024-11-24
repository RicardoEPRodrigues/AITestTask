// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyCoordinator.generated.h"

UCLASS()
class AITESTTASK_API AEnemyCoordinator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyCoordinator();

	/**
	 * Class to search for when finding enemies to control.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	TSubclassOf<class AAIController> EnemyCharacterClass;

	/**
	 * Blackboard key to set the enemy is attacking.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	FName IsAttackingKey{ "IsAttacking" };

	/**
	 * Blackboard key to check if the enemy has attacked.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	FName HasAttackedKey{ "HasAttacked" };

	/**
	 * Interval between attacks.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	float AttackInterval{ 5.0f };

	/**
	 * Deduction from the attack interval after each attack.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Enemy")
	float AttackIntervalDeduction{ 0.2f };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<class AAIController*> FoundAIControllers{};

	UPROPERTY()
	class AAIController* AttackingController{};

	UPROPERTY()
	FTimerHandle TimerHandle{};

	/**
	 * Determines which NPC should be attacking and which should be defending.
	 */
	UFUNCTION()
	void CoordinateAttack();
	
	UPROPERTY(BlueprintReadOnly, Category = "Enemy")
	float CurrentAttackInterval{};

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
