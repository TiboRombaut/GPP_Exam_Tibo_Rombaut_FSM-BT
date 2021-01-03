#include "stdafx.h"
#include "Plugin.h"
#include "IExamInterface.h"
#include "Behaviours.h"
using namespace Elite;
//Called only once, during initialization
void Plugin::Initialize(IBaseInterface* pInterface, PluginInfo& info)
{
	//Retrieving the interface
	//This interface gives you access to certain actions the AI_Framework can perform for you
	m_pInterface = static_cast<IExamInterface*>(pInterface);

	//Bit information about the plugin
	//Please fill this in!!
	info.BotName = "BotNameTEST";
	info.Student_FirstName = "Foo";
	info.Student_LastName = "Bar";
	info.Student_Class = "2DAEx";

	//Called when the plugin is loaded
	Elite::Blackboard* pBlackboard = new Elite::Blackboard();
	pBlackboard->AddData("Agent", m_pInterface->Agent_GetInfo());
	pBlackboard->AddData("Target", Elite::Vector2{});
	pBlackboard->AddData("Wanderangle", m_WanderAngle);
	pBlackboard->AddData("EnemiesInFOV", GetEntitiesInFOV());
	pBlackboard->AddData("RunMode", m_RunMode);
	pBlackboard->AddData("Inventory", m_Inventory);
	pBlackboard->AddData("InterFace", m_pInterface);
	pBlackboard->AddData("HousesInFOV", GetHousesInFOV());
	pBlackboard->AddData("IsPathFinding", bool{ false });//stops when the target is the center then he can save the last point
	pBlackboard->AddData("EndGoalPathFinding", Elite::Vector2{ 10000,10000 });
	pBlackboard->AddData("LastPathPointPos", Elite::Vector2{});
	pBlackboard->AddData("IsInHouse", bool{ false });
	pBlackboard->AddData("CanLeaveHouse", bool{ false });
	pBlackboard->AddData("HousesToSkip", m_housesToSkip);
	pBlackboard->AddData("NodeCounterToLeaveHouse", int{ 0 });
	pBlackboard->AddData("LastKnowLocationOutsideHoude", Elite::Vector2{ 0.0f,0.0f });
	pBlackboard->AddData("ShootingTarget", Elite::Vector2{ 0.0f,0.0f });
	pBlackboard->AddData("canShoot", bool{ false });
	pBlackboard->AddData("AllowedToShoot", bool {false});
	pBlackboard->AddData("Bitten", bool{ false });
	pBlackboard->AddData("MaxHealth" ,float{ 10.0f });
	pBlackboard->AddData("MaxEnergy", float{ 10.0f });


	//m_pBT = new BehaviorTree(pBlackboard,
	//	new BehaviorSelector({
	//		new BehaviorSequence({
	//			new BehaviorConditional(CanPickUpItem),
	//			new BehaviorAction(AddToInventory)
	//			}),
	//		new BehaviorSequence({
	//			new BehaviorConditional(IsInHouse),
	//			new BehaviorAction(ChangeToSeek)
	//			}),
	//		new BehaviorSequence({
	//			new BehaviorConditional(HousesInFOV),
	//			new BehaviorAction(ChangeToSeek)
	//			}),
	//		new BehaviorAction(ChangeToWander)
	//	})
	//);
	//m_pBT = new BehaviorTree(pBlackboard,
	//	new BehaviorSelector({
	//		new BehaviorSequence(
	//			{
	//				new BehaviorConditional(NeedsFood),
	//				new BehaviorAction(UseFoodKit)
	//			}),
	//		new BehaviorSequence(
	//			{
	//				new BehaviorConditional(NeedsHealth),
	//				new BehaviorAction(UseMedKit)
	//			}),
	//			new BehaviorSequence(
	//			{
	//				new BehaviorConditional(IsBittenAndHasAmmo),
	//				new BehaviorAction(TurnAround)
	//			}),
	//			new BehaviorSequence({
	//				new BehaviorConditional(CanPickUpItem),
	//				new BehaviorAction(AddToInventory)
	//			}), // hier ergens een fout dat ihj niet omdraait wss iets daje terug op false zet nu geen goesting om te zoeken xD
	//			new BehaviorSequence({
	//				new BehaviorConditional(EnemyInFOV),
	//				new BehaviorSequence
	//				(
	//					{
	//						new BehaviorConditional(HasAmmo),
	//						new BehaviorAction(Shoot)
	//						//new BehaviorAction(ChangeToEvade)
	//					}
	//				)
	//			})

	//		//new BehaviorAction(ChangeToWander)
	//		})
	//);
	m_pBT = new BehaviorTree(pBlackboard,
		new BehaviorSelector({
			new BehaviorSequence(
				{
					new BehaviorConditional(NeedsFood),
					new BehaviorAction(UseFoodKit)
				}),
			new BehaviorSequence(
				{
					new BehaviorConditional(NeedsHealth),
					new BehaviorAction(UseMedKit)
				}),
			new BehaviorSequence({
				new BehaviorConditional(CanPickUpItem),
				new BehaviorAction(AddToInventory)
			}), // hier ergens een fout dat ihj niet omdraait wss iets daje terug op false zet nu geen goesting om te zoeken xD
			new BehaviorSequence({
							new BehaviorConditional(IsInHouse),
							new BehaviorAction(ChangeToSeek)
							}),
			new BehaviorSequence({
					new BehaviorConditional(HousesInFOV),
					new BehaviorAction(ChangeToSeek)
			}),
			//new BehaviorSequence(
			//{
			//	new BehaviorConditional(IsBittenAndHasAmmo),
			//	new BehaviorAction(TurnAround)
			//}),
			new BehaviorSequence({
				new BehaviorConditional(EnemyInFOV),
				new BehaviorSequence
				(
					{
						new BehaviorConditional(HasAmmo),
						new BehaviorAction(Shoot)
						//new BehaviorAction(ChangeToEvade)
					}
				)
			}),
				new BehaviorAction(ChangeToWander)
		})
	);
	std::cout << "test";

}


//Called only once
void Plugin::DllInit()
{

}

//Called only once
void Plugin::DllShutdown()
{
	//Called wheb the plugin gets unloaded
}

//Called only once, during initialization
void Plugin::InitGameDebugParams(GameDebugParams& params)
{
//	params.LevelFile = "LevelTwo.gppl";
	params.AutoFollowCam = true; //Automatically follow the AI? (Default = true)
	params.RenderUI = true; //Render the IMGUI Panel? (Default = true)
	params.SpawnEnemies = true; //Do you want to spawn enemies? (Default = true)
	params.EnemyCount = 20; //How many enemies? (Default = 20)
	params.GodMode = false; //GodMode > You can't die, can be usefull to inspect certain behaviours (Default = false)
	params.AutoGrabClosestItem = true; //A call to Item_Grab(...) returns the closest item that can be grabbed. (EntityInfo argument is ignored)
}

//Only Active in DEBUG Mode
//(=Use only for Debug Purposes)
void Plugin::Update(float dt)
{
	//m_pBT->GetBlackboard()->ChangeData("Agent", m_pInterface->Agent_GetInfo());
	//m_pBT->GetBlackboard()->ChangeData("Target", m_Target);
	//m_pBT->GetBlackboard()->ChangeData("EnemiesInFOV", GetEntitiesInFOV());
	//m_pBT->GetBlackboard()->ChangeData("HousesInFOV", GetHousesInFOV());
	//m_pBT->GetBlackboard()->ChangeData("Bitten", m_pInterface->Agent_GetInfo().Bitten);
	//m_pBT->Update(dt);

	//Elite::Vector2 target;
	//Elite::Vector2 shootTarget;
	//auto dataAvaible = m_pBT->GetBlackboard()->GetData("Target", target) &&
	//m_pBT->GetBlackboard()->GetData("RunMode", m_RunMode) && 
	//m_pBT->GetBlackboard()->GetData("ShootingTarget", shootTarget);
	//if (dataAvaible == true)
	//{
	//	m_Target = target;
	//	m_TargetShoot = shootTarget;
	//	//std::cout << shootTarget.x << ", " << shootTarget.y;
	//}
	//std::cout << "hall";
	UpdateSteering(dt);

	//if (m_Timer > 10.0f) {
	//	m_Timer = 0.0f;
	//}
	//m_Timer += dt;
	//Demo Event Code
	//In the end your AI should be able to walk around without external input
	if (m_pInterface->Input_IsMouseButtonUp(Elite::InputMouseButton::eLeft))
	{
		//Update target based on input
		Elite::MouseData mouseData = m_pInterface->Input_GetMouseData(Elite::InputType::eMouseButton, Elite::InputMouseButton::eLeft);
		const Elite::Vector2 pos = Elite::Vector2(static_cast<float>(mouseData.X), static_cast<float>(mouseData.Y));
		m_Target = m_pInterface->Debug_ConvertScreenToWorld(pos);
	}
	else if (m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_Space))
	{
		m_CanRun = true;
	}
	else if (m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_Left))
	{
		m_AngSpeed -= Elite::ToRadians(10);
	}
	else if (m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_Right))
	{
		m_AngSpeed += Elite::ToRadians(10);
	}
	else if (m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_G))
	{
		//system("pause");
		m_GrabItem = true;
	}
	else if (m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_U))
	{
		m_UseItem = true;
	}
	else if (m_pInterface->Input_IsKeyboardKeyDown(Elite::eScancode_R))
	{
		m_RemoveItem = true;
	}
	else if (m_pInterface->Input_IsKeyboardKeyUp(Elite::eScancode_Space))
	{
		m_CanRun = false;
	}
}

Elite::Blackboard* Plugin::CreateBlackboard()
{
	Elite::Blackboard* pBlackboard = new Elite::Blackboard();
	//pBlackboard->AddData("Agent", m_pInterface->Agent_GetInfo());
	pBlackboard->AddData("Target", Elite::Vector2{5.0f,5.0f});
	return pBlackboard;
}

//Update
//This function calculates the new SteeringOutput, called once per frame
SteeringPlugin_Output Plugin::UpdateSteering(float dt)
{
	m_pBT->GetBlackboard()->ChangeData("Agent", m_pInterface->Agent_GetInfo());
	m_pBT->GetBlackboard()->ChangeData("Target", m_Target);
	m_pBT->GetBlackboard()->ChangeData("EnemiesInFOV", GetEntitiesInFOV());
	m_pBT->GetBlackboard()->ChangeData("HousesInFOV", GetHousesInFOV());
	m_pBT->GetBlackboard()->ChangeData("Bitten", m_pInterface->Agent_GetInfo().Bitten);
	m_pBT->Update(dt);

	Elite::Vector2 target;
	Elite::Vector2 shootTarget;
	auto dataAvaible = m_pBT->GetBlackboard()->GetData("Target", target) &&
	m_pBT->GetBlackboard()->GetData("RunMode", m_RunMode) && 
	m_pBT->GetBlackboard()->GetData("ShootingTarget", shootTarget);
	if (dataAvaible == true)
	{
		m_Target = target;
		m_TargetShoot = shootTarget;
		//std::cout << shootTarget.x << ", " << shootTarget.y;
	}

	auto steering = SteeringPlugin_Output();

	//Use the Interface (IAssignmentInterface) to 'interface' with the AI_Framework
	auto agentInfo = m_pInterface->Agent_GetInfo();

	auto nextTargetPos = m_Target; //To start you can use the mouse position as guidance

	auto vHousesInFOV = GetHousesInFOV();//uses m_pInterface->Fov_GetHouseByIndex(...)
	auto vEntitiesInFOV = GetEntitiesInFOV(); //uses m_pInterface->Fov_GetEntityByIndex(...)
	for (auto& e : vEntitiesInFOV)
	{
		if (e.Type == eEntityType::PURGEZONE)
		{
			PurgeZoneInfo zoneInfo;
			m_pInterface->PurgeZone_GetInfo(e, zoneInfo);
			std::cout << "Purge Zone in FOV:" << e.Location.x << ", "<< e.Location.y <<  " ---EntityHash: " << e.EntityHash << "---Radius: "<< zoneInfo.Radius << std::endl;
		}
	}
	

	//INVENTORY USAGE DEMO
	//********************

	if (m_GrabItem)
	{
		ItemInfo item;
		//Item_Grab > When DebugParams.AutoGrabClosestItem is TRUE, the Item_Grab function returns the closest item in range
		//Keep in mind that DebugParams are only used for debugging purposes, by default this flag is FALSE
		//Otherwise, use GetEntitiesInFOV() to retrieve a vector of all entities in the FOV (EntityInfo)
		//Item_Grab gives you the ItemInfo back, based on the passed EntityHash (retrieved by GetEntitiesInFOV)
		if (m_pInterface->Item_Grab({}, item))
		{
			//Once grabbed, you can add it to a specific inventory slot
			//Slot must be empty
			m_pInterface->Inventory_AddItem(0, item);
		}
	}

	if (m_UseItem)
	{
		//Use an item (make sure there is an item at the given inventory slot)
		m_pInterface->Inventory_UseItem(0);
	}

	if (m_RemoveItem)
	{
		//Remove an item from a inventory slot
		m_pInterface->Inventory_RemoveItem(0);
	}


	switch (m_RunMode)
	{
	case RunMode::Seek:
		steering.LinearVelocity = (m_Target)-agentInfo.Position; //Desired Velocity
		steering.LinearVelocity.Normalize(); //Normalize desired Velocity
		steering.LinearVelocity *= agentInfo.MaxLinearSpeed; //Rescale to max speed
		break;
	case RunMode::Evade:
	{
		m_CanRun = true;
		steering.LinearVelocity = m_Target; //Desired Velocity
		steering.LinearVelocity.Normalize(); //Normalize Desired Velocity
		steering.LinearVelocity *= -(agentInfo.MaxLinearSpeed); //Rescale to Max Speed

	}
	default:
		break;
	}
	if (agentInfo.WasBitten)
	{
		m_pBT->GetBlackboard()->ChangeData("Bitten", bool{ true });

	}
	else
	{
		m_pBT->GetBlackboard()->ChangeData("Bitten", bool{ false });

	}
	//steering.LinearVelocity = (m_Target)-agentInfo.Position; //Desired Velocity
	//steering.LinearVelocity.Normalize(); //Normalize desired Velocity
	//steering.LinearVelocity *= agentInfo.MaxLinearSpeed; //Rescale to max speed


	//Simple Seek Behaviour (towards Target)
	//steering.LinearVelocity = nextTargetPos - agentInfo.Position; //Desired Velocity
	//steering.LinearVelocity.Normalize(); //Normalize Desired Velocity
	//steering.LinearVelocity *= agentInfo.MaxLinearSpeed; //Rescale to Max Speed

	if (Distance(nextTargetPos, agentInfo.Position) < 2.f)
	{
		steering.LinearVelocity = Elite::ZeroVector2;
	}
	bool orientation;
	m_pBT->GetBlackboard()->GetData("canShoot", orientation);
	if (orientation)
	{
		std::cout << "hal";
		steering.AutoOrient = false; //Setting AutoOrientate to TRue overrides the AngularVelocity

		//Elite::Vector2 direction{m_TargetShoot - agentInfo.Position };
		//float desiredOrientation = Elite::GetOrientationFromVelocity(direction);

		auto enemyEntities = GetEntitiesInFOV();
		EntityInfo currentEnemy;
		for (int i = 0; i < enemyEntities.size(); i++)
		{
			if (enemyEntities[i].Type == eEntityType::ENEMY)
			{
				currentEnemy = enemyEntities[i];
				m_TargetShoot = currentEnemy.Location;
			}
		}
		//std::cout <<"shoot : " << m_TargetShoot.x << " , " << m_TargetShoot.y << std::endl;
		//std::cout << "target : " << m_Target.x << " , " << m_Target.y << std::endl;
		//std::cout << "agent : " << agentInfo.Position.x << " , " << agentInfo.Position.y << std::endl;

		float targetAngle = Elite::GetOrientationFromVelocity(m_TargetShoot - agentInfo.Position);
		float currentAngle = agentInfo.Orientation;
		float changeAngle = targetAngle - currentAngle;
		
		//clamp value
		while (changeAngle < float(-M_PI))
		{
			changeAngle += 2.0f * float(M_PI);
		}
		while (changeAngle > float(M_PI))
		{
			changeAngle -= 2.0f * float(M_PI);
		}

		steering.AngularVelocity = changeAngle * agentInfo.MaxAngularSpeed;

		Elite::Vector2 newVectorAB{ currentEnemy.Location - agentInfo.Position };
		Elite::Vector2 normalizedVector{ OrientationToVector(agentInfo.Orientation) };

		float angle{ acos(((newVectorAB.x * normalizedVector.x) + (newVectorAB.y * normalizedVector.y)) /
			(sqrt(Elite::Square(newVectorAB.x) + Elite::Square(newVectorAB.y)) * sqrt(Elite::Square(normalizedVector.x) + Elite::Square(normalizedVector.y)))) };

		//calc current angle
		float DistanceEnemy{ Elite::Distance(currentEnemy.Location,agentInfo.Position) };
		float halfEnemyWidth{ agentInfo.AgentSize / 2 };

		float minAngle = atan(halfEnemyWidth / DistanceEnemy);
		
		if (angle < minAngle && angle > 0.0f)
		{
			
		//	std::cout << "halloplus   ";
			m_pBT->GetBlackboard()->ChangeData("AllowedToShoot", true);
		}
		else if (angle > -minAngle && angle < 0.0f)
		{
		//	std::cout << "hallomin   ";

			m_pBT->GetBlackboard()->ChangeData("AllowedToShoot", true);
		}
		//float result{ desiredOrientation - orientation };
		//if (result < 0.0001f)
		//{
		//	m_pBT->GetBlackboard()->ChangeData("AllowedToShoot", bool{ true });

		//}
		//if (agentInfo.Orientation < desiredOrientation)
		//{
		//	steering.AngularVelocity = agentInfo.MaxAngularSpeed;
		//}
		//else
		//{
		//	steering.AngularVelocity = -agentInfo.MaxAngularSpeed;
		//}


	}
	else
	{
		steering.AutoOrient = true;
	}



	steering.RunMode = m_CanRun; //If RunMode is True > MaxLinSpd is increased for a limited time (till your stamina runs out)

								 //SteeringPlugin_Output is works the exact same way a SteeringBehaviour output

								 //@End (Demo Purposes)
	m_GrabItem = false; //Reset State
	m_UseItem = false;
	m_RemoveItem = false;

	return steering;
}

//This function should only be used for rendering debug elements
void Plugin::Render(float dt) const
{
	//This Render function should only contain calls to Interface->Draw_... functions
	m_pInterface->Draw_SolidCircle(m_Target, .7f, { 0,0 }, { 1, 0, 0 });
}

vector<HouseInfo> Plugin::GetHousesInFOV() const
{
	vector<HouseInfo> vHousesInFOV = {};

	HouseInfo hi = {};
	for (int i = 0;; ++i)
	{
		if (m_pInterface->Fov_GetHouseByIndex(i, hi))
		{
			vHousesInFOV.push_back(hi);
			continue;
		}

		break;
	}

	return vHousesInFOV;
}

vector<EntityInfo> Plugin::GetEntitiesInFOV() const
{
	vector<EntityInfo> vEntitiesInFOV = {};

	EntityInfo ei = {};
	for (int i = 0;; ++i)
	{
		if (m_pInterface->Fov_GetEntityByIndex(i, ei))
		{
			vEntitiesInFOV.push_back(ei);
			continue;
		}

		break;
	}

	return vEntitiesInFOV;
}
