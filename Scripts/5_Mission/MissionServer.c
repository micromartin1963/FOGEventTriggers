modded class MissionServer
{
	void MissionServer()
    {     

	 FOG__Info config;

	FOGTriggerConfig.LoadConfig("FOGTRiggersConfig.json",config);

	GetDayZGame().SetFTRConfig(config);



  		
	if (GetGame().IsServer()) 
        {
	FOGTriggers.ClearInstance();
	FOGTriggers.GetInstance();
        }
		
    }
};