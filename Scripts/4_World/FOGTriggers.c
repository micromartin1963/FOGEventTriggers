class FOGTriggers
{
	protected static ref FOGTriggers Instance;
	
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
		GetRPCManager().AddRPC( "FOGTriggers", "StopTrigger", this, SingleplayerExecutionType.Client );   // Don't know yet !!!!!!!!!!
		FOG__Info config = GetDayZGame().GetFTRConfig(); 
		FOG_MYTrigger trigger;
		vector mins, maxs;

		vector WhereIsIt = config.FOGLocs.Get(1).OrigVectorStr.ToVector();

		float radius = 5.8;                  // bring in from file

			trigger = FOG_MYTrigger.Cast(GetGame().CreateObject("FOG_MYTrigger", WhereIsIt));

			if (radius == 0)
			{
				trigger.SetExtents(mins, maxs);
			} else {
				trigger.SetCollisionCylinder(radius, 5.8);   // check this ???????
			}  
			trigger.SetTriggerType(config.FOGLocs.Get(1).TType);
			trigger.SetTriggerText(config.FOGLocs.Get(1).name);
  			trigger.SetTriggerOrigVector(config.FOGLocs.Get(1).OrigVectorStr);
			trigger.SetTargetVectorStr(config.FOGLocs.Get(1).TargetVectorStr);
			trigger.SetLastTriggeredTime((GetGame().GetTime()/1000) );

		GetGame().CreateObject("FOGNPC_SurvivorM_Mirek", "10810 4 2266");	// this is just a visual marker temp	
       }
	
	//void StopTrigger( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )  // ????????????????????????????
	//{
	//}

	static void FogSteppedIntoArea2(Object obj, string str,string positionOrig)
	{
		//----TO DO CHECK TYPE AND  DOCASE RESULTS --------------------------------------------------------
		vector where;
		where = positionOrig.ToVector();
                PlayerBase player = PlayerBase.Cast(obj);

		Param1<string> msgRp0 = new Param1<string>( str );
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgRp0, true, player.GetIdentity());

		GetGame().CreateObject("FOGNPC_SurvivorM_Mirek", where);

	}

}