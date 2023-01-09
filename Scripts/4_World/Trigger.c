

class FOG_MYTrigger extends Trigger
{
	protected int m_FOGtrigger;
	protected  EffectSound m_FOGtriggerSound;
	protected string m_TriggerText;
	protected string m_TriggerOrigVector;
	protected string m_TriggerTargetRot;
	//protected int m_TriggerSnd;
        protected int m_type;
        protected int m_soundindex;
        protected int m_standdowntime;
	protected string m_FOGClassname;
	protected int m_LastTriggered; 
	protected int m_ShowMarker
	protected int m_LastTriggeredTime ;  
	protected string m_TriggerTargetVector;
	protected int m_SoundLoopTime;
	
	void FOG_MYTrigger()
	{
		RegisterNetSyncVariableInt("m_FOGtrigger");
	}
			
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if (m_FOGtrigger>0)
		{
		DoStuff("FOG_SoundSet_"  + m_FOGtrigger.ToString());
		}
        }
	

	void DoStuff(string sndstr)
	{
	FOGTriggers.FOGSteppedIntoAreaFromSync(sndstr);
	}




	void TriggerOnEnterEvent(int index)
	{
		m_FOGtrigger = index;
		SetSynchDirty();
	}
	
	void ResetEvent()
	{
		m_FOGtrigger = 0;
		SetSynchDirty();
	}

	void SetFOGClassname(string Cn)
	{
		m_FOGClassname = Cn;
	}
	
	string GetFOGClassname()
	{
		return m_FOGClassname;
	}
	
	void SetFOGSoundIndex(int i)
	{
		m_soundindex = i;
	}

	int GetFOGSoundIndex()
	{
		return m_soundindex;
	}


	void SetTriggerType(int t)
	{
		m_type = t;
	}
	
	int GetTriggerType()
	{
		return m_type;
	}

	void SetStandDownTime(int time)
	{
		m_standdowntime = time;
	}
	
	int GetStandDownTime()
	{
		return m_standdowntime;
	}

	string GetTargetVectorStr()
	{
	return m_TriggerTargetVector;
	}

	void SetTargetVectorStr(string v)
	{
	m_TriggerTargetVector = v;
	}

	string GetTriggerOrigVector()
	{
	return m_TriggerOrigVector;
	}

	void SetTargetRotation(string r)
	{
	m_TriggerTargetRot = r;
	}

	string GetTargetRotation()
	{
	return m_TriggerTargetRot;
	}

	void SetTriggerOrigVector(string v)
	{
	m_TriggerOrigVector = v;
	}

	 string GetTriggerText()
	{
		return m_TriggerText;
	}

	void SetTriggerText(string text)
	{
		m_TriggerText = text;
	}

	int GetShowMarker()
	{
		return m_ShowMarker;
	}

	void SetShowMarker(int i)
	{
		m_ShowMarker = i;
	}


	//int GetTriggerSnd()
	//{
	//	return m_TriggerSnd;
	//}

	//void SetTriggerSnd(int i)
	//{
	//	m_TriggerSnd = i;
	//}

	void SetLastTriggeredTime(int mytime)
	{
		m_LastTriggeredTime = mytime;
	}

	int GetLastTriggeredTime()
	{
		return m_LastTriggeredTime;
	}

	bool CanWeTrigger(int mytime)  
	{
		if (mytime > m_LastTriggeredTime + GetStandDownTime())
		{
		m_LastTriggeredTime = mytime;
		return true;
		}			
		return false;
	}
		
	void OnEnter(Object obj)
	{				
		if (obj.IsMan() && GetGame().IsServer())
		{
			if (PlayerBase.Cast(obj).GetIdentity())
			{
				if (PlayerBase.Cast(obj).GetIdentity().GetName())
				{
					if (CanWeTrigger(GetGame().GetTime()/1000))
					{
					PlayerBase player = PlayerBase.Cast(obj);	
					string vectorstr1 = GetTargetVectorStr();
					string FClassname = GetFOGClassname();
					string txtstr =  GetTriggerText();
					int TriggerType = GetTriggerType();
					int sndIndex = GetFOGSoundIndex(); 	
					SetLastTriggeredTime(GetGame().GetTime()/1000);
					FOGTriggers.FOGSteppedIntoArea(obj,txtstr,vectorstr1,FClassname,TriggerType); 
					TriggerOnEnterEvent(sndIndex);  
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ResetEvent, 1000, false );   // 1000 should be GetStandDownTime ??   
					//FOGTriggers.FOGSteppedIntoArea(obj,txtstr,vectorstr1,FClassname,TriggerType);   -------------------moved to see if longer teleport works
					}
				}
			}
		}					
	}

	void OnLeave(Object obj)
	{    
	}

};