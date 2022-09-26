class FOG_MYTrigger extends Trigger
{
	protected int m_fogtrigger;
	protected  EffectSound m_fogtriggerSound;
	protected string m_TriggerText;
	protected string m_TriggerOrigVector;
	protected string m_TriggerSnd;
        protected int m_type;
	protected int m_LastTriggered; //----------------------------------------------------------
	protected int m_LastTriggeredTime;
	protected string m_TriggerTargetVector;
	
	void FOG_MYTrigger()
	{
		RegisterNetSyncVariableInt("m_fogtrigger");
	}
	
	void StopMyTriggeredEvent()
	{
		GetRPCManager().SendRPC( "FOGTriggers", "StopTrigger", new Param1< vector >( this.GetPosition() ) );
	}
		
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		if (m_fogtrigger>0)
		{
		string sndstr  = "FOG_SoundSet_001";  // COMPOSE SOUNDSET FROME NAME AND INDEX > sndstr
		DoMyTriggeredEvent(m_fogtrigger,sndstr);

		}
        }
	
	void DoMyTriggeredEvent(int index,string sndstr)
	{
		PlaySoundSet(m_fogtriggerSound, sndstr, 0.1, 0.1);  
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
	
	void SetTriggerType(int t)
	{
		m_type = t;
	}
	
	int GetTriggerType()
	{
		return m_type;
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


	bool CanWeTrigger(int time)   //------------- 60 needs to be a variable
	{
		if (time > m_LastTriggeredTime+60)
		{
			m_LastTriggered = time;
			return true;
		}			
		return false;
	}
		
	void OnEnter(Object obj)
    {

	string txtstr = GetTriggerText();
	string vectorstr1 = GetTargetVectorStr();
					
		if (obj.IsMan() && GetGame().IsServer())
		{
			if (CanWeTrigger(GetGame().GetTime()/1000))
			{
			SetLastTriggeredTime(GetGame().GetTime()/1000);
			TriggerOnEnterEvent(1);    // -calls this action to call DoMyTriggeredEvent but this has parameter limitations. so call FogSteppedIntoArea(obj) aswell !???!!!
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ResetEvent, 1000, false );         // needed to reset
			FOGTriggers.FogSteppedIntoArea2(obj,txtstr,vectorstr1);   //calls this action aswell !!! needed to use playerbase ?!? (more parameters to be pushed)
			}
		}					
    }

    void OnLeave(Object obj)
    {    
    }

};