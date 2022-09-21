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
		GetRPCManager().AddRPC( "FOGTriggers", "FOGMessage", this, SingleplayerExecutionType.Client );
		FOG_MYTrigger trigger;
		vector mins, maxs;
		vector WhereIsIt = "10810 4 2266";
		float radius = 5.8;

			

			trigger = FOG_MYTrigger.Cast(GetGame().CreateObject("FOG_MYTrigger", WhereIsIt));

			if (radius == 0)
			{
				trigger.SetExtents(mins, maxs);
			} else {
				trigger.SetCollisionCylinder(radius, 5.8);
			}    

		GetGame().CreateObject("FOGNPC_SurvivorM_Mirek", "10810 4 2266");		
       }



	
	void StopTrigger( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{


	}





}