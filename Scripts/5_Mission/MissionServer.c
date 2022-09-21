modded class MissionServer
{
	void MissionServer()
    {       		
	if (GetGame().IsServer()) 
        {
	FOGTriggers.ClearInstance();
	FOGTriggers.GetInstance();
        }
		
    }
};