// 1 teleport , 2 spawn item , 3 sound only

class FOG_MYTrigger extends Trigger
{
	protected int m_fogtrigger;
	protected  EffectSound m_fogtriggerSound;
	protected string m_TriggerText;
	protected string m_TriggerOrigVector;
	protected string m_TriggerTargetRot;
	protected string m_TriggerSnd;
        protected int m_type;
        protected int m_soundindex;
        protected int m_standdowntime;
	protected string m_FogClassname;
	protected int m_LastTriggered; //----------------------------------------------------------
	protected int m_LastTriggeredTime;
	protected string m_TriggerTargetVector;
	
	void FOG_MYTrigger()
	{
		RegisterNetSyncVariableInt("m_fogtrigger");
	}
			
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if (m_fogtrigger>0)
		{
		DoStuff("FOG_SoundSet_" + m_fogtrigger.ToString());
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

	string GetTriggerSnd()
	{
		return m_TriggerSnd;
	}

	void SetTriggerSnd(string text)
	{
		m_TriggerSnd = text;
	}

	void SetLastTriggeredTime(int time)
	{
		m_LastTriggeredTime = time;
	}


	bool CanWeTrigger(int time)   //------------- 60 needs to be a variable possibly not less that 60
	{
		if (time > m_LastTriggeredTime + GetStandDownTime())
		{
			m_LastTriggered = time;
			return true;
		}			
		return false;
	}
		
	void OnEnter(Object obj)
    {
				
		if (obj.IsMan() && GetGame().IsServer())
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
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ResetEvent, 1000, false );      
			FOGTriggers.FogSteppedIntoArea(obj,txtstr,vectorstr1,FClassname,TriggerType);  
			}
		}					
    }

    void OnLeave(Object obj)
    {    
    }

};