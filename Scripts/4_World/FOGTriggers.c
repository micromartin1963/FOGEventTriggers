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
			trigger.SetShowMarker(config.FOGLocs.Get(i).ShowMarker);
			trigger.SetLastTriggeredTime((GetGame().GetTime()/1000) );
				if(config.FOGLocs.Get(i).ShowMarker == 1)
				{
				GetGame().CreateObject("FOGSign_Marker", WhereIsIt );   // temp visual  marker ------------------------------
				}
	  }
       }
	
	static void FogSteppedIntoArea(Object obj, string textstr,string targetvectorstr,string classnamestr,int TriggerType)
	{
		//type 2 - teleport , 3 - spawn object , 4 -  message , 5 - teleport + message , 6 - spawn + message

                PlayerBase player = PlayerBase.Cast(obj);
		Param1<string> msgRp0 = new Param1<string>( textstr );
		FogTriggerLogger.Log("In Zone");

		if(TriggerType==2)
		{
		player.SetPosition(targetvectorstr.ToVector());	
		}

		if(TriggerType==3)
		{
			if(classnamestr.Contains("ZmbM") || classnamestr.Contains("FOGPseudoGiant") )
			{
			GetGame().CreateObject(classnamestr, targetvectorstr.ToVector(),false,true,true );
			FogTriggerLogger.Log("spawned  AI " + classnamestr);
			}
			else
			{
			GetGame().CreateObject(classnamestr, targetvectorstr.ToVector());
			FogTriggerLogger.Log("spawned NON AI " + classnamestr);
			}
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
			if(classnamestr.Contains("ZmbM") || classnamestr.Contains("FOGPseudoGiant") )
			{
			GetGame().CreateObject(classnamestr, targetvectorstr.ToVector(),false,true,true );
			FogTriggerLogger.Log("spawned AI " + classnamestr);
			}
			else
			{
			GetGame().CreateObject(classnamestr, targetvectorstr.ToVector());
			FogTriggerLogger.Log("spawned NON AI " + classnamestr);
			}
		}	
	}


	static void FogSteppedIntoAreaFromSync(string textstr)

	//!!!!!!! soundset format suggest FOG_SoundSet_XYYNNN
	// X = type (see below) , Y = seconds of loop , NNN sounset num
	// 1 = play at trigger point (No loop)

	// 3 = play on person (No loop)
	// 4 = play at trigger pos (loop for YY seconds)

	// 6 = play on person (loop for YY seconds)

	// 320003  eg FOG_SoundSet_620003 plays on person for 20 seconds
	// 100001     FOG_SoundSet_100001 plays at trigger point once
	// 160001     FOG_SoundSet_120001 will not play at trigger point once because its type one ,so YY is ignored ! it should be 420001

	{
	string snd = "" + textstr;
	int TrType = GetTriggerType(snd);
	int TrLoopTime = GetTriggerSeconds(snd);

	PlayerBase player = GetGame().GetPlayer();
		if(player)
		{
		vector whereamI = player.GetPosition();

		EffectSound m_fogtriggerSound2 = new EffectSound;
			if(TrType==1) // play at trigger pos
			{
			m_fogtriggerSound2 = SEffectManager.PlaySound( snd, whereamI ,0.0,0.0,false); // testing loop
			}

			if(TrType==3) // play on person
			{
			m_fogtriggerSound2 = SEffectManager.PlaySoundOnObject( snd, player );  // testing on person to be moved
			m_fogtriggerSound2.SetSoundAutodestroy(true);
			}

			if(TrType==4) // play triggerpos   and loop
			{
			m_fogtriggerSound2 = SEffectManager.PlaySound( snd, whereamI ,0.0,0.0,true); // testing loop
			m_fogtriggerSound2.SetSoundAutodestroy(true);
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(ResetSound,(TrLoopTime*1000) ,false, m_fogtriggerSound2);
			}

			if(TrType==6) // play on person and loop
			{
			m_fogtriggerSound2 = SEffectManager.PlaySoundOnObject( snd, player, 0.0 ,0.0,true );  // testing on person to be moved
			m_fogtriggerSound2.SetSoundAutodestroy(true);
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater(ResetSound,(TrLoopTime*1000) ,false, m_fogtriggerSound2);
			}
		}
	}

	static void ResetSound(EffectSound m)
	{
	delete m;
	}

	static int GetTriggerType(string txtIn) // get 13'th char convert to int
	{
	int result = 0;
	string str = txtIn.Get(13);
	result=str.ToInt();
	return result;
	}

	static int GetTriggerSeconds(string txtIn) // get 14 + 15 convert to int THIS NEEDS TRIMMING !!!!
	{
	int result = 0;
	string temp ="";
	string temp2 ="";
	string tempboth ="";
	temp = txtIn.Get(14);
	temp2 = txtIn.Get(15);
	tempboth = temp + temp2;
	result=tempboth.ToInt();
	return result;
	}

}