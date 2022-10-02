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
	FOG__Info config = GetDayZGame().GetFTRConfig(); 
	FOG_MYTrigger trigger;
	  for ( int i=0; i < config.FOGLocs.Count(); i++)
	  {
		vector WhereIsIt = config.FOGLocs.Get(i).OrigVectorStr.ToVector();

		float radius =  config.FOGLocs.Get(i).FogRadius.ToFloat();              

			trigger = FOG_MYTrigger.Cast(GetGame().CreateObject("FOG_MYTrigger", WhereIsIt));

			if (radius == 0)
			{
			trigger.SetCollisionCylinder(10, 5.9);   // Just set a default 
			}
			else
			{
			trigger.SetCollisionCylinder(radius, 5.9);
			}  
			trigger.SetTriggerType(config.FOGLocs.Get(i).TType);
			trigger.SetTriggerText(config.FOGLocs.Get(i).FogText);
  			trigger.SetTriggerOrigVector(config.FOGLocs.Get(i).OrigVectorStr);
			trigger.SetTargetVectorStr(config.FOGLocs.Get(i).TargetVectorStr);
			trigger.SetFogSoundIndex(config.FOGLocs.Get(i).FogSoundIndex);
			trigger.SetFogClassname(config.FOGLocs.Get(i).FogClassnameStr);
			trigger.SetTargetRotation(config.FOGLocs.Get(i).TargetRot);
			trigger.SetStandDownTime(config.FOGLocs.Get(i).StandDownTime);
			trigger.SetLastTriggeredTime((GetGame().GetTime()/1000) );
	    GetGame().CreateObject("FOGNPC_SurvivorM_Mirek", WhereIsIt );   // temp visual  marker ------------------------------
	  }
       }
	
	static void FogSteppedIntoArea(Object obj, string textstr,string targetvectorstr,string classnamestr,int TriggerType)
	{
		//type 2 - teleport , 3 - spawn object , 4 -  message , 5 - teleport + message , 6 - spawn + message
	
                PlayerBase player = PlayerBase.Cast(obj);
		Param1<string> msgRp0 = new Param1<string>( textstr );

		if(TriggerType==2)
		{
		player.SetPosition(targetvectorstr.ToVector());	
		}
		if(TriggerType==3)
		{
		GetGame().CreateObject(classnamestr, targetvectorstr.ToVector() );
		}

		if(TriggerType==4)
		{
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgRp0, true, player.GetIdentity());
		}

		if(TriggerType==5)
		{
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgRp0, true, player.GetIdentity());
		player.SetPosition(targetvectorstr.ToVector());	
		}

		if(TriggerType==6)
		{
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, msgRp0, true, player.GetIdentity());
		GetGame().CreateObject(classnamestr, targetvectorstr.ToVector() );
		}

		if(TriggerType==7)
		{

		}

	





	
	}

	static void FogSteppedIntoAreaFromSync(string textstr)  
	{
	string snd = "" + textstr;
	PlayerBase player = GetGame().GetPlayer();
		if(player)
		{
		vector where = player.GetPosition();
		EffectSound m_fogtriggerSound2 = new EffectSound;
		m_fogtriggerSound2 = SEffectManager.PlaySound( snd, where );
		}
		else
		{
		Print("Error in FogSteppedIntoAreaFromSync");
		}
	}
}