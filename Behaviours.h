/*=============================================================================*/
// Copyright 2020-2021 Elite Engine
/*=============================================================================*/
// Behaviors.h: Implementation of certain reusable behaviors for the BT version of the Agario Game
/*=============================================================================*/
#ifndef ELITE_APPLICATION_BEHAVIOR_TREE_BEHAVIORS
#define ELITE_APPLICATION_BEHAVIOR_TREE_BEHAVIORS
//-----------------------------------------------------------------
// Includes & Forward Declarations
//-----------------------------------------------------------------
#include "stdafx.h"
#include "IExamInterface.h"
#include "Structs.h"

//-----------------------------------------------------------------
// Helper functions
//-----------------------------------------------------------------
float distanceSingleDigit(float number1, float number2)
{
	number1 += 10000;
	number2 += 10000;
	if (number1 > number2)
	{
		return number1 - number2;
	}
	else 
	{
		return number2 - number1;
	}
}


//-----------------------------------------------------------------
// Behaviors
//-----------------------------------------------------------------
bool NothingInFOV(Elite::Blackboard* pBlackboard)
{
	std::cout << "travelnot ";

	vector<HouseInfo> houses;
	AgentInfo OurAgent;
	Elite::Vector2 target;
	IExamInterface* pInterFace = nullptr;
	bool isPathFinding;
	Elite::Vector2 endGoal;
	Elite::Vector2 LastPathPoint;
	bool canLeaveHouse;
	bool isInHouse;
	std::vector<HouseInfo> housesToSkip;
	int counter;
	Elite::Vector2 LastKnownLocation;
	Elite::Vector2 currentHouseEntrance;
	std::vector<PointsOfInterestIsSkippable> pointsOfInterest;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("HousesInFOV", houses)
		&& pBlackboard->GetData("InterFace", pInterFace) && pBlackboard->GetData("IsPathFinding", isPathFinding)
		&& pBlackboard->GetData("EndGoalPathFinding", endGoal) && pBlackboard->GetData("LastPathPointPos", LastPathPoint)
		&& pBlackboard->GetData("CanLeaveHouse", canLeaveHouse) && pBlackboard->GetData("IsInHouse", isInHouse)
		&& pBlackboard->GetData("HousesToSkip", housesToSkip) && pBlackboard->GetData("NodeCounterToLeaveHouse", counter)
		&& pBlackboard->GetData("LastKnowLocationOutsideHoude", LastKnownLocation) && pBlackboard->GetData("HouseEntrance", currentHouseEntrance)
		&& pBlackboard->GetData("pointsOfInterest", pointsOfInterest);

	Elite::Vector2 currentTarget{ 0.0f,0.0f };

	//if (Elite::Distance(OurAgent.Position, endGoal) < 2.0f)
	//{
	//	pBlackboard->ChangeData("IsInHouse", true);
	//}

	//if (isInHouse)
	//{
	//	//std::cout << "out";
	//	pBlackboard->ChangeData("Target", LastKnownLocation);
	//	return true;
	//}

	//if (isPathFinding)
	//{
	//	//pBlackboard->ChangeData("ShootingTarget",endGoal );
	//	//pBlackboard->ChangeData("canShoot", bool{ true });
	//	currentTarget = pInterFace->NavMesh_GetClosestPathPoint(endGoal);
	//	if (currentTarget != endGoal)
	//	{
	//		//std::cout << "changes";
	//		pBlackboard->ChangeData("LastPathPointPos", currentTarget);
	//	}
	//	pBlackboard->ChangeData("Target", currentTarget);
	//	return true;
	//}

	//if (houses.size() == 0)
	//{
		float closestDistance{ 9999.f };
		float closestHouse{ 0 };
		bool canGoToHouse{ false };
		for (int i = 0; i < pointsOfInterest.size(); i++)
		{
			if (!pointsOfInterest[i].canSkip)
			{
				float distance{ Elite::Distance(pointsOfInterest[i].location,OurAgent.Position) };
				if (distance < closestDistance)
				{
					std::cout << "niet goed";
					closestDistance = distance;
					closestHouse = i;
					canGoToHouse = true;
				}
			}
		}
		if (canGoToHouse)
		{
			pBlackboard->ChangeData("EndGoalPathFinding", pointsOfInterest[closestHouse].location);

			currentTarget = pInterFace->NavMesh_GetClosestPathPoint(pointsOfInterest[closestHouse].location);
			if (currentTarget != endGoal)
			{
				//std::cout << "changes";
				pBlackboard->ChangeData("LastPathPointPos", currentTarget);
			}
			pBlackboard->ChangeData("Target", currentTarget);
			//	pBlackboard->ChangeData("IsPathFinding", true);
			return true;
		}
	//}
	return false;
}

bool EnemyInFOV(Elite::Blackboard* pBlackboard)
{

	vector<EntityInfo> enemies;
	AgentInfo OurAgent;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("EnemiesInFOV", enemies);
	//std::cout << "hello";

	//if (!dataAvailable)
	//	return false;
	//std::cout << "hello";


	if (enemies.size() > 0)
	{
		//std::cout << "good";
		//Elite::Vector2 currentTarget{ 0.0f,0.0f };
		//float closestDistance{ 9999.f };
		//for (int i = 0; i < enemies.size(); i++)
		//{
		//	float distance{ Elite::Distance(enemies[i].Location,OurAgent.Position) };
		//	if (distance < closestDistance)
		//	{
		//		closestDistance = distance;
		//		currentTarget = enemies[i].Location;
		//	}
		//}
		//pBlackboard->ChangeData("Target", currentTarget);
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].Type == eEntityType::ENEMY)
			{
				return true;
			}
		}
	}
	return false;
}

bool IsBittenAndHasAmmo(Elite::Blackboard* pBlackboard)
{
	bool isBitten;
	std::vector<InventorySlots> inventory;

	auto dataAvailable = pBlackboard->GetData("Bitten", isBitten) && pBlackboard->GetData("Inventory", inventory);

	//if (!dataAvailable)
	//	return false;
	//std::cout << "hello";

	if (!isBitten)
	{
		return false;
	}
	return true;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].type == eItemType::PISTOL)
		{
			std::cout << "hellp";

			return true;
		}
	}
	return false;
}

bool NeedsFood(Elite::Blackboard* pBlackboard)
{
	AgentInfo OurAgent;
	std::vector<InventorySlots> inventory;
	float maxEnergy;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("Inventory", inventory)
		&& pBlackboard->GetData("MaxHealth", maxEnergy);

	int currentItem{ 0 };
	bool hasFoundItem{ false };
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].type == eItemType::FOOD)
		{
			currentItem = i;
			hasFoundItem = true;
		}
	}

	if (!hasFoundItem)
	{
		return false;
	}

	if (OurAgent.Energy < maxEnergy - inventory[currentItem].amount)
	{
		return true;
	}

	return false;
}

bool NeedsHealth(Elite::Blackboard* pBlackboard)
{
	AgentInfo OurAgent;
	std::vector<InventorySlots> inventory;
	float maxHealth;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent)  && pBlackboard->GetData("Inventory", inventory)
	 && pBlackboard->GetData("MaxHealth", maxHealth);

	int currentItem{ 0 };
	bool hasFoundItem{ false };
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].type == eItemType::MEDKIT)
		{
			currentItem = i;
			hasFoundItem = true;
		}
	}

	if (!hasFoundItem)
	{
		return false;
	}

	if (OurAgent.Health < maxHealth - inventory[currentItem].amount)
	{
		return true;
	}

	return false;
}

bool IsInHouse(Elite::Blackboard* pBlackboard)
{
	//std::cout << "Inhouse ";
	vector<HouseInfo> houses;
	AgentInfo OurAgent;
	Elite::Vector2 target;
	vector<EntityInfo> entities;

	IExamInterface* pInterFace = nullptr;
	bool isPathFinding;
	Elite::Vector2 endGoal;
	Elite::Vector2 LastPathPoint;
	Elite::Vector2 currentHouseEntrance;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("HousesInFOV", houses)
		&& pBlackboard->GetData("InterFace", pInterFace) && pBlackboard->GetData("IsPathFinding", isPathFinding)
		&& pBlackboard->GetData("EndGoalPathFinding", endGoal) && pBlackboard->GetData("LastPathPointPos", LastPathPoint)
		&& pBlackboard->GetData("EnemiesInFOV", entities) && pBlackboard->GetData("HouseEntrance", currentHouseEntrance);
	
	

	if (houses.size() > 0)
	{
		if(distanceSingleDigit(houses[0].Center.x,OurAgent.Position.x) < houses[0].Size.x/2, distanceSingleDigit(houses[0].Center.y, OurAgent.Position.y) < houses[0].Size.y/2)
		{
			//if (Elite::Distance(currentHouseEntrance, endGoal) < houses[0].Size.x)
			//{
			//	pBlackboard->ChangeData("HouseEntrance", OurAgent.Position);
			//}
			//for (int i = 0; i < entities.size(); i++)
			//{
			//	if (entities[i].Type == eEntityType::ITEM)
			//	{
			//	//	std::cout << "good";
			//		pBlackboard->ChangeData("IsInHouse", true);
			//		pBlackboard->ChangeData("Target", entities[i].Location);
			//		return true;
			//	}
			//}
			//std::cout << "good ";
			//pBlackboard->ChangeData("IsInHouse", true);
			return false;
		}
	}
	pBlackboard->ChangeData("LastKnowLocationOutsideHoude", OurAgent.Position);
	pBlackboard->ChangeData("IsInHouse", false);
	return false;
}

bool CanPickUpItem(Elite::Blackboard* pBlackboard)
{
	//std::cout << "pickup ";

	AgentInfo OurAgent;
	Elite::Vector2 target;
	vector<EntityInfo> entities;
	IExamInterface* pInterFace = nullptr;

	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent)
		&& pBlackboard->GetData("InterFace", pInterFace)
		&& pBlackboard->GetData("EnemiesInFOV", entities);

	if (entities.size() > 0)
	{
		for (int i = 0; i < entities.size(); i++)
		{
			if (entities[i].Type == eEntityType::ITEM)
			{
				if (Elite::Distance(OurAgent.Position, entities[i].Location) < 2.0f)
				{
					//pBlackboard->ChangeData("Target", entities[i].Location);
					return true;
				}
			}
		}
	}
	//pBlackboard->ChangeData("canShoot", false);

	return false;
}

bool HousesInFOV(Elite::Blackboard* pBlackboard)
{
	//std::cout << "travel ";
	
	vector<HouseInfo> houses;
	AgentInfo OurAgent;
	Elite::Vector2 target;
	IExamInterface* pInterFace = nullptr;
	bool isPathFinding;
	Elite::Vector2 endGoal;
	Elite::Vector2 LastPathPoint;
	bool canLeaveHouse;
	bool isInHouse;
	std::vector<HouseInfo> housesToSkip;
	int counter;
	Elite::Vector2 LastKnownLocation;
	Elite::Vector2 currentHouseEntrance;
	std::vector<PointsOfInterestIsSkippable> pointsOfInterest;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("HousesInFOV", houses)
	&& pBlackboard->GetData("InterFace", pInterFace) && pBlackboard->GetData("IsPathFinding", isPathFinding)
		&& pBlackboard->GetData("EndGoalPathFinding", endGoal) && pBlackboard->GetData("LastPathPointPos", LastPathPoint)
		&& pBlackboard->GetData("CanLeaveHouse", canLeaveHouse) && pBlackboard->GetData("IsInHouse", isInHouse)
	&& pBlackboard->GetData("HousesToSkip", housesToSkip) && pBlackboard->GetData("NodeCounterToLeaveHouse", counter)
	&&	pBlackboard->GetData("LastKnowLocationOutsideHoude", LastKnownLocation) && pBlackboard->GetData("HouseEntrance", currentHouseEntrance)
	&& pBlackboard->GetData("pointsOfInterest", pointsOfInterest);

	
	Elite::Vector2 currentTarget{ 0.0f,0.0f };
	
	if (houses.size() > 0)
	{
		for (int i = 0; i < housesToSkip.size(); i++)
		{
			if (houses[0].Center == housesToSkip[i].Center)
			{
				return false;
			}
		}
		pBlackboard->ChangeData("EndGoalPathFinding", houses[0].Center);
		if (Elite::Distance(OurAgent.Position, endGoal) < 2.0f)
		{
			//disbaling all the points of interest of this house
			for (int i = 0; i < pointsOfInterest.size(); i++)
			{
				if (distanceSingleDigit(houses[0].Center.x, pointsOfInterest[i].location.x) < houses[0].Size.x / 2 + 3.0f, distanceSingleDigit(houses[0].Center.y, pointsOfInterest[i].location.y) < houses[0].Size.y / 2 + 3.0f)
				{
					pointsOfInterest[i].canSkip = true;
				}
			}
			housesToSkip.push_back(houses[0]);
			pBlackboard->ChangeData("HousesToSkip", housesToSkip);
			pBlackboard->ChangeData("pointsOfInterest", pointsOfInterest);
			pBlackboard->ChangeData("IsInHouse", true);
		}
	}
	if (isInHouse)
	{
		pBlackboard->ChangeData("Target", LastKnownLocation);
		return true;
	}
	if (isPathFinding)
	{

		//pBlackboard->ChangeData("ShootingTarget",endGoal );
		//pBlackboard->ChangeData("canShoot", bool{ true });
		currentTarget = pInterFace->NavMesh_GetClosestPathPoint(endGoal);
		if (currentTarget != endGoal)
		{
			//std::cout << "changes";
			pBlackboard->ChangeData("LastPathPointPos", currentTarget);
		}
		pBlackboard->ChangeData("Target", currentTarget);
		return true;
	}

	if (houses.size() > 0)
	{
		float closestDistance{ 9999.f };
		float closestHouse{ 0 };
		for (int i = 0; i < houses.size(); i++)
		{
			float distance{ Elite::Distance(houses[i].Center,OurAgent.Position) };
			if (distance < closestDistance)
			{
				closestDistance = distance;
				closestHouse = i;
			}
		}
		pBlackboard->ChangeData("EndGoalPathFinding", houses[closestHouse].Center);

		currentTarget = pInterFace->NavMesh_GetClosestPathPoint(houses[closestHouse].Center);
		if (currentTarget != endGoal)
		{
			//std::cout << "changes";
			pBlackboard->ChangeData("LastPathPointPos", currentTarget);
		}
		pBlackboard->ChangeData("Target", currentTarget);
		pBlackboard->ChangeData("IsPathFinding", true);
		return true;
	}
	return false;
	//if (isInHouse == false)
	//{
	//	pBlackboard->ChangeData("CanLeaveHouse", false);

	//	return false;
	//}

	//if (Elite::Distance(OurAgent.Position, LastPathPoint) < 2.0f)
	//{
	//	currentTarget = houses[closestHouse].Center;
	//}
	//else
	//{
	//	pBlackboard->ChangeData("LastPathPointPos", currentTarget);
	//}

	//if (currentTarget == houses[closestHouse].Center)
	//{
	//	pBlackboard->ChangeData("IsPathFinding", false);
	//}
	//else
	//{
	//	pBlackboard->ChangeData("IsPathFinding", true);
	//}
	//if (houses.size() > 0)
	//{
	//	for (int i = 0; i < housesToSkip.size(); i++)
	//	{
	//		if (houses[0].Center == housesToSkip[i].Center)
	//		{
	//			return false;
	//		}
	//	}
	//}

	//if (canLeaveHouse)
	//{ 
	//	//Elite::Vector2 OutsideGoal{};
	//	//OutsideGoal.x = houses[0].Center.x;
	//	//OutsideGoal.y = houses[0].Center.y + houses[0].Size.y;

	//	Elite::Vector2 outsideTarget{ pInterFace->NavMesh_GetClosestPathPoint(LastKnownLocation) };

	//	if (Elite::Distance(OurAgent.Position, outsideTarget) < 2.0f)
	//	//if(!isInHouse)
	//	{
	//			pBlackboard->ChangeData("CanLeaveHouse", false);
	//			if (housesToSkip.size() == 0)
	//			{
	//				housesToSkip.push_back(houses[0]);
	//				pBlackboard->ChangeData("HousesToSkip", housesToSkip);
	//			}
	//			else
	//			{
	//				bool IsInVector{ false };
	//				for (int i = 0; i < housesToSkip.size(); i++)
	//				{
	//					if (houses[0].Center == housesToSkip[i].Center)
	//					{
	//						IsInVector = true;
	//					}
	//				}
	//				if (!IsInVector)
	//				{
	//					housesToSkip.push_back(houses[0]);
	//					pBlackboard->ChangeData("HousesToSkip", housesToSkip);
	//				}
	//			}
	//			pBlackboard->ChangeData("Target", LastKnownLocation);
	//		pBlackboard->ChangeData("NodeCounterToLeaveHouse", counter);

	//		return false;
	//	}
	//	pBlackboard->ChangeData("Target", outsideTarget);
	//	return true;
	//}

	//if (Elite::Distance(OurAgent.Position, endGoal) < 2.0f)
	//{
	//	
	//	pBlackboard->ChangeData("CanLeaveHouse", true);
	//}

	//if(isPathFinding)
	//{ 
	//	//std::cout << "heelo";
	//	currentTarget = pInterFace->NavMesh_GetClosestPathPoint(endGoal);
	//	if (Elite::Distance(OurAgent.Position,LastPathPoint)< 2.0f )
	//	{
	//		//std::cout << "    yaaay   ";
	//		currentTarget = endGoal;
	//		pBlackboard->ChangeData("Target", currentTarget);
	//	}
	//	else if (currentTarget == endGoal)
	//	{
	//		pBlackboard->ChangeData("IsPathFinding", false);
	//	}
	//	else
	//	{
	//		pBlackboard->ChangeData("IsPathFinding", true);
	//	}
	//	return true;
	//}
	//else if (houses.size() > 0 )
	//{
	//	std::cout << "jw";
	//	float closestDistance{ 9999.f };
	//	float closestHouse{ 0 };
	//	for (int i = 0; i < houses.size(); i++)
	//	{
	//		float distance{ Elite::Distance(houses[i].Center,OurAgent.Position) };
	//		if (distance < closestDistance)
	//		{
	//			closestDistance = distance;
	//			closestHouse = i;
	//		}
	//	}
	//	pBlackboard->ChangeData("EndGoalPathFinding", houses[closestHouse].Center);

	//	currentTarget = pInterFace->NavMesh_GetClosestPathPoint(houses[closestHouse].Center);

	//	if (Elite::Distance(OurAgent.Position, LastPathPoint) < 2.0f)
	//	{
	//		currentTarget = houses[closestHouse].Center;
	//	}
	//	else
	//	{
	//		pBlackboard->ChangeData("LastPathPointPos", currentTarget);
	//	}

	//	if (currentTarget == houses[closestHouse].Center)
	//	{
	//		pBlackboard->ChangeData("IsPathFinding", false);
	//	}
	//	else
	//	{
	//		pBlackboard->ChangeData("IsPathFinding", true);
	//	}
	//	pBlackboard->ChangeData("Target", currentTarget);
	//	//pBlackboard->ChangeData("IsPathFinding", true);
	//	return true;
	//}
	return false;
}

bool HasAmmo(Elite::Blackboard* pBlackboard)
{
	vector<EntityInfo> enemies;
	AgentInfo OurAgent;
	std::vector<InventorySlots> inventory;

	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("EnemiesInFOV", enemies)
		&& 	pBlackboard->GetData("Inventory", inventory);

	//if (!dataAvailable)
	//	return false;
	//std::cout << "hello";
	bool hasAmmo{ false };
//	int amountAmmo{ 0 };
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].type == eItemType::PISTOL)
		{
			hasAmmo = true;
			//maybe you can do something that if he has so many lives he need so many bullets
			//if (inventory[i].amount > amountAmmo)
			//{
			//	amountAmmo = inventory[i].amount;
			//}
		}
	}
	//hasAmmo = true;
	if (hasAmmo)
	{
	//	std::cout << "ammo";

		if (enemies.size() > 0)
		{
		//	std::cout << "good";
			Elite::Vector2 currentTarget{ 0.0f,0.0f };
			float closestDistance{ 9999.f };
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].Type == eEntityType::ENEMY)
				{
					float distance{ Elite::Distance(enemies[i].Location,OurAgent.Position) };
					if (distance < closestDistance)
					{
						closestDistance = distance;
						currentTarget = enemies[i].Location;
					}
				}
			}
			//std::cout << "hello";
			pBlackboard->ChangeData("canShoot", bool{ true });
			pBlackboard->ChangeData("ShootingTarget", currentTarget);
			//pBlackboard->ChangeData("Target", currentTarget);
			return true;
		}
	}
	//std::cout << "goof";
	pBlackboard->ChangeData("canShoot", bool{ false });
	//pBlackboard->ChangeData("AllowedToShoot", false);

	return false;
}

Elite::BehaviorState UseFoodKit(Elite::Blackboard* pBlackboard)
{
	AgentInfo OurAgent;
	IExamInterface* pInterFace = nullptr;
	std::vector<InventorySlots> inventory;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("Inventory", inventory)
		&& pBlackboard->GetData("InterFace", pInterFace);

	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}

	int currentItem{ 0 };
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].type == eItemType::FOOD)
		{
			currentItem = i;
		}
	}

	pInterFace->Inventory_UseItem(currentItem);
	pInterFace->Inventory_RemoveItem(currentItem);
	inventory[currentItem].amount = 0;
	inventory[currentItem].type = eItemType::GARBAGE;
	pBlackboard->ChangeData("Inventory", inventory);

	return  Elite::BehaviorState::Success;
}

Elite::BehaviorState UseMedKit(Elite::Blackboard* pBlackboard)
{
	AgentInfo OurAgent;
	IExamInterface* pInterFace = nullptr;
	std::vector<InventorySlots> inventory;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("Inventory", inventory)
		&& pBlackboard->GetData("InterFace", pInterFace);

	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}

	int currentItem{ 0 };
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i].type == eItemType::MEDKIT)
		{
			currentItem = i;
		}
	}

	pInterFace->Inventory_UseItem(currentItem);
	pInterFace->Inventory_RemoveItem(currentItem);
	inventory[currentItem].amount = 0;
	inventory[currentItem].type = eItemType::GARBAGE;
	pBlackboard->ChangeData("Inventory", inventory);

	return  Elite::BehaviorState::Success;
}

Elite::BehaviorState TurnAround(Elite::Blackboard* pBlackboard)
{
	AgentInfo OurAgent;
	Elite::Vector2 target;
	Elite::Vector2 newTarget{ 0.0f,0.0f };

	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("Target", target);

	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}

	float distance{ Elite::Distance(OurAgent.Position,target) };;
	
	if (target.x > OurAgent.Position.x)
	{
		newTarget.x = OurAgent.Position.x - distance;
	}
	else
	{
		newTarget.x = OurAgent.Position.x + distance;
	}

	if (target.y > OurAgent.Position.y)
	{
		newTarget.y = OurAgent.Position.y - distance;
	}
	else
	{
		newTarget.y = OurAgent.Position.y + distance;
	}
	std::cout << "top";
	pBlackboard->ChangeData("ShootingTarget", newTarget);
	pBlackboard->ChangeData("canShoot", bool{ true });

	return  Elite::BehaviorState::Success;

}

Elite::BehaviorState Shoot(Elite::Blackboard* pBlackboard)
{
	vector<EntityInfo> enemies;
	AgentInfo OurAgent;
	std::vector<InventorySlots> inventory;
	IExamInterface* pInterFace = nullptr;
	bool orientationToShootGood;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("EnemiesInFOV", enemies)
		&& pBlackboard->GetData("Inventory", inventory) && pBlackboard->GetData("InterFace", pInterFace)
	&& pBlackboard->GetData("AllowedToShoot",orientationToShootGood);
	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}

	//
	if (orientationToShootGood)
	{
		//std::cout << "shoot";

		for (int i = 0; i < inventory.size(); i++)
		{
			if (inventory[i].type == eItemType::PISTOL)
			{
				pInterFace->Inventory_UseItem(i);
				inventory[i].amount--;
				if (inventory[i].amount <= 0)
				{
					pInterFace->Inventory_RemoveItem(i);
				}
				//maybe you can do something that if he has so many lives he need so many bullets
				//if (inventory[i].amount > amountAmmo)
				//{
				//	amountAmmo = inventory[i].amount;
				//}
				pBlackboard->ChangeData("canShoot", false);
				pBlackboard->ChangeData("AllowedToShoot", false);
				pBlackboard->ChangeData("Inventory", inventory);
			}
		}

	}

	return Elite::BehaviorState::Success;
}

Elite::BehaviorState ChangeToSeek(Elite::Blackboard* pBlackboard)
{
	Elite::Vector2 target;
	auto dataAvailable = pBlackboard->GetData("Target", target);
	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}

	pBlackboard->ChangeData("Target", target);
	pBlackboard->ChangeData("RunMode", RunMode::Seek);

	return Elite::BehaviorState::Success;
}

Elite::BehaviorState ChangeToWander(Elite::Blackboard* pBlackboard)
{
	AgentInfo pAgent;
	Elite::Vector2 target;
	float wanderAngle = 0.0f;
	bool isPathFinding;
	IExamInterface* pInterFace = nullptr;
	auto dataAvailable = pBlackboard->GetData("Agent", pAgent) 
		&&  pBlackboard->GetData("Target", target) && pBlackboard->GetData("Wanderangle",wanderAngle)
		&& pBlackboard->GetData("IsPathFinding", isPathFinding) && pBlackboard->GetData("InterFace", pInterFace);
	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}

	if (isPathFinding)
	{
		return Elite::BehaviorState::Failure;
	}
	float offset = 10.0f;
	float radius{ 4.0f };
//	std::cout << "wander  ";

	float AngleChanfe{ Elite::ToRadians(45.f) };
	Elite::Vector2 direction = pAgent.LinearVelocity;
	direction.Normalize();
	Elite::Vector2 posCircle = pAgent.Position + direction * offset;

	wanderAngle += Elite::randomFloat(-AngleChanfe, AngleChanfe);

	target.x = posCircle.x + cos(wanderAngle) * radius;
	target.y = posCircle.y + sin(wanderAngle) * radius;


	//IsInBounds
	Elite::Vector2 dimensions = pInterFace->World_GetInfo().Dimensions;
	if (target.x > dimensions.x / 2)
	{
		float distance = distanceSingleDigit(target.x, dimensions.x);
		target.x -= 2 * distance;

	}
	else if (target.x < -dimensions.x / 2)
	{
		float distance = distanceSingleDigit(target.x, -dimensions.x);
		target.x += 2 * distance;
	}

	if (target.y > dimensions.y / 2)
	{
		float distance = distanceSingleDigit(target.y, dimensions.y);
		target.x -= 2 * distance;
	}
	else if (target.y < -dimensions.y / 2)
	{
		float distance = distanceSingleDigit(target.y, -dimensions.y);
		target.y += 2 * distance;
	}

	//std::cout << dimensions.x << " , " << dimensions.y << std::endl;
	pBlackboard->ChangeData("Target", target);
	pBlackboard->ChangeData("Wanderangle", wanderAngle);
	pBlackboard->ChangeData("RunMode", RunMode::Seek);

	return Elite::BehaviorState::Success;
}

Elite::BehaviorState ChangeToEvade(Elite::Blackboard* pBlackboard)
{
	AgentInfo OurAgent;
	Elite::Vector2 target;
	float wanderAngle = 0.0f;
	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent)
		&& pBlackboard->GetData("Target", target) && pBlackboard->GetData("Wanderangle", wanderAngle);
	if (!dataAvailable)
	{
		std::cout << "fail";
		return Elite::BehaviorState::Failure;
	}
//	auto distanceToTarget = Distance(OurAgent.Position,target);
	//float fleeRadius{ 15.0f };
	//if (distanceToTarget > fleeRadius)
	//{
	//	std::cout << "enough distance";
	//	return Elite::BehaviorState::Failure;
	//}

	float distance = (Distance(target, OurAgent.Position));
	float Prediction{ distance / 20 };
//	std::cout << "evade    ";
	target = target + OurAgent.LinearVelocity * Prediction;
	target = target - OurAgent.Position * Prediction; //Desired Velocity
//	steering.LinearVelocity.Normalize(); //Normalize Desired Velocity
//	steering.LinearVelocity *= -(OurAgent.MaxLinearSpeed); //Rescale to Max Speed
	pBlackboard->ChangeData("RunMode", RunMode::Evade);
	pBlackboard->ChangeData("Target", target);

	return Elite::BehaviorState::Success;
}

Elite::BehaviorState AddToInventory(Elite::Blackboard* pBlackboard)
{
	//std::cout << "addtoinventort ";
	vector<InventorySlots> inventory;
	AgentInfo OurAgent;
	IExamInterface* pInterFace = nullptr;

	auto dataAvailable = pBlackboard->GetData("Agent", OurAgent) && pBlackboard->GetData("Inventory", inventory)
		&& pBlackboard->GetData("InterFace", pInterFace);

	ItemInfo item;
	pInterFace->Item_Grab({}, item);
	
	int amount{ 0 };

	switch (item.Type)
	{
	case eItemType::FOOD:
		amount = pInterFace->Food_GetEnergy(item);
		std::cout << "food" << std::endl;
		break;
	case eItemType::MEDKIT:
		amount = pInterFace->Medkit_GetHealth(item);
		std::cout << "medkit" << std::endl;
		break;
	case eItemType::PISTOL:
		amount = pInterFace->Weapon_GetAmmo(item);
		std::cout << "pistol" << std::endl;
		break;
	case eItemType::GARBAGE:
		std::cout << "garbage" << std::endl;
		break;
	case eItemType::RANDOM_DROP_WITH_CHANCE:
		std::cout << "chance" << std::endl;
		break;
	case eItemType::RANDOM_DROP:
		std::cout << "random;" << std::endl;
		break;
	//case eItemType::_LAST:
	//	std::cout << "last" << std::endl;
	//	break;

	default:
		std::cout << "nothing good" << std::endl;
		break;
	}
	if (item.Type != eItemType::GARBAGE)
	{
		if (inventory.size() < 5)
		{
			pInterFace->Inventory_AddItem(inventory.size(), item);
			inventory.push_back(InventorySlots{ item.Type,amount });
		}
		else
		{
			int pistolCounter{ 0 };
			int medKitCounter{ 0 };
			int foodCounter{ 0 };
			for (int i = 0; i < inventory.size(); i++)
			{
		/*		ItemInfo item;
				pInterFace->Inventory_GetItem(0, item);*/

				switch (inventory[i].type)
				{
				case eItemType::FOOD:
					foodCounter++;
					break;
				case eItemType::MEDKIT:
					medKitCounter++;
					break;
				case eItemType::PISTOL:
					pistolCounter++;
					break;
				default:
					break;
				}
			}

			int lowestScore{ 1000 };
			int NumberToDelete{0};
			if (foodCounter > 2)
			{
				for (int i = 0; i < inventory.size(); i++)
				{
					if (inventory[i].type == eItemType::FOOD)
					{
						if (inventory[i].amount < lowestScore)
						{
							lowestScore = inventory[i].amount;
							NumberToDelete = i;
						}
					}
				}
			}
			else if (pistolCounter > 2)
			{
				for (int i = 0; i < inventory.size(); i++)
				{
					if (inventory[i].type == eItemType::PISTOL)
					{
						if (inventory[i].amount < lowestScore)
						{
							lowestScore = inventory[i].amount;
							NumberToDelete = i;
						}
					}
				}
			}
			else if(medKitCounter>2)
			{
				for (int i = 0; i < inventory.size(); i++)
				{
					if (inventory[i].type == eItemType::MEDKIT)
					{
						if (inventory[i].amount < lowestScore)
						{
							lowestScore = inventory[i].amount;
							NumberToDelete = i;
						}
					}
				}
			}
			pInterFace->Inventory_RemoveItem(NumberToDelete);
			pInterFace->Inventory_AddItem(NumberToDelete, item);
			inventory[NumberToDelete] = InventorySlots{ item.Type,amount };

		}
		pBlackboard->ChangeData("Inventory", inventory);
		//pBlackboard->ChangeData("InterFace", pInterFace);
		return Elite::BehaviorState::Success;
	}
	else
	{

		//pInterFace->Item_Destroy(item.ItemHash);
	}
	return Elite::BehaviorState::Failure;
}
#endif