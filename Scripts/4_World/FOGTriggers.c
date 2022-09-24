class FOGTriggers
{

	protected static ref FOGTriggers Instance;
	//protected ref array<FOG_MYTrigger> XYZTriggers = new array<FOG_MYTrigger>; // don't think this get used at the moment
	
	static FOGTriggers GetInstance()
	{
		if (!Instance)
        {
            Instance = new FOGTriggers();
        }
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}
	
	void FOGTriggers()
        {
		GetRPCManager().AddRPC( "FOGTriggers", "StopTrigger", this, SingleplayerExecutionType.Client );
		FOG__Info config = GetDayZGame().GetFTRConfig(); 
		FOG_MYTrigger trigger;
		vector mins, maxs;
		vector WhereIsIt = "10810 4 2266";   // temp fixed position
		float radius = 5.8;                  // bring in from file

			trigger = FOG_MYTrigger.Cast(GetGame().CreateObject("FOG_MYTrigger", WhereIsIt));

			if (radius == 0)
			{
				trigger.SetExtents(mins, maxs);
			} else {
				trigger.SetCollisionCylinder(radius, 5.8);   // check this ???????
			}  
			trigger.SetTriggerText("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
  

		GetGame().CreateObject("FOGNPC_SurvivorM_Mirek", "10810 4 2266");	// this is just a visual marker temp	
       }
	
	void StopTrigger( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
	}

	static void FogSteppedIntoArea(Object obj, string str)
	{
                PlayerBase player = PlayerBase.Cast(obj);
		Param1<string> msgRp0 = new Param1<string>( str );
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgRp0, true, player.GetIdentity());
	}
}