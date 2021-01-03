#pragma once
#include "IExamPlugin.h"
#include "Exam_HelperStructs.h"
#include "stdafx.h"
#include "Structs.h"

class IBaseInterface;
class IExamInterface;

class Plugin :public IExamPlugin
{
public:
	Plugin() {};
	virtual ~Plugin() {};

	void Initialize(IBaseInterface* pInterface, PluginInfo& info) override;
	void DllInit() override;
	void DllShutdown() override;

	void InitGameDebugParams(GameDebugParams& params) override;
	void Update(float dt) override;

	SteeringPlugin_Output UpdateSteering(float dt) override;
	void Render(float dt) const override;
	Elite::Blackboard* CreateBlackboard();

private:
	//Interface, used to request data from/perform actions with the AI Framework
	IExamInterface* m_pInterface = nullptr;
	vector<HouseInfo> GetHousesInFOV() const;
	vector<EntityInfo> GetEntitiesInFOV() const;

	Elite::Vector2 m_Target = {};
	Elite::Vector2 m_TargetShoot = {};

	bool m_CanRun = false; //Demo purpose
	bool m_GrabItem = false; //Demo purpose
	bool m_UseItem = false; //Demo purpose
	bool m_RemoveItem = false; //Demo purpose
	float m_AngSpeed = 0.f; //Demo purpose

	//	//own 
	float m_Timer{ 1.1f };
	Elite::BehaviorTree* m_pBT;
	float m_WanderAngle{ 0.0f };
	RunMode m_RunMode{ RunMode::Seek };
	std::vector<InventorySlots> m_Inventory;
	std::vector<HouseInfo> m_housesToSkip;
};

//ENTRY
//This is the first function that is called by the host program
//The plugin returned by this function is also the plugin used by the host program
extern "C"
{
	__declspec (dllexport) IPluginBase* Register()
	{
		return new Plugin();
	}
}