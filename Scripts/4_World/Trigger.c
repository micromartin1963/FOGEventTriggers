

class FOG_MYTrigger extends Trigger
{
	protected int m_fogtrigger;
	protected  EffectSound m_fogtriggerSound;
	protected string m_TriggerText;
	protected string m_TriggerOrigVector;
	protected string m_TriggerTargetRot;
	//protected int m_TriggerSnd;
        protected int m_type;
        protected int m_soundindex;
        protected int m_standdowntime;
	protected string m_FogClassname;
	protected int m_LastTriggered; 
	protected int m_ShowMarker
	protected int m_LastTriggeredTime ;  
	protected string m_TriggerTargetVector;
	protected int m_SoundLoopTime;
	
	void FOG_MYTrigger()
	{
		RegisterNetSyncVariableInt("m_fogtrigger");
	}
			
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if (m_fogtrigger>0)
		{
		DoStuff("FOG_SoundSet_"  + m_fogtrigger.ToString());
		}
        }
	

	void DoStuff(string sndstr)
	{
	FOGTriggers.FogSteppedIntoAreaFromSync(sndstr);
	}




	void TriggerOnEnterEvent(int index)
	{
		m_fogtrigger = index;
		SetSynchDirty();
	}
	
	void ResetEvent()
	{
		m_fogtrigger = 0;
		SetSynchDirty();
	}

	void SetFogClassname(string Cn)
	{
		m_FogClassname = Cn;
	}
	
	string GetFogClassname()
	{
		return m_FogClassname;
	}
	
	void SetFogSoundIndex(int i)
	{
		m_soundindex = i;
	}

	int GetFogSoundIndex()
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
					string FClassname = GetFogClassname();
					string txtstr =  GetTriggerText();
					int TriggerType = GetTriggerType();
					int sndIndex = GetFogSoundIndex(); 	
					SetLastTriggeredTime(GetGame().GetTime()/1000);
					TriggerOnEnterEvent(sndIndex);  
					GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ResetEvent, 1000, false );   // 1000 should be GetStandDownTime ??   
					FOGTriggers.FogSteppedIntoArea(obj,txtstr,vectorstr1,FClassname,TriggerType); 
					}
				}
			}
		}					
	}

	void OnLeave(Object obj)
	{    
	}

};