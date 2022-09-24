class FOG_MYTrigger extends Trigger
{
	protected int m_fogtrigger;
	protected ref EffectSound m_fogtriggerSound;
	protected string m_TriggerText;
	protected string m_TriggerOrigVector;
	
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
			DoMyTriggeredEvent(m_fogtrigger);
		}
        }
	
	void DoMyTriggeredEvent(int index)
	{
		m_fogtriggerSound = SEffectManager.PlaySoundOnObject( "ZmbM_Normal2_FOG_001_SoundSet", this );
		m_fogtriggerSound.Event_OnSoundWaveEnded.Insert(StopMyTriggeredEvent);
		m_fogtriggerSound.SetSoundAutodestroy(true);
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
		
	void OnEnter(Object obj)
    {

	string str = GetTriggerText();
	vector WhereIsIt = "10810 4 2266";                                     // just one fixed test position till bring fileread in
	string str2 = "10825 4 2278";
		if (vector.Distance(this.GetPosition(), WhereIsIt) <= 20.0)	// will bring in variable for radius
		{
		TriggerOnEnterEvent(1);    // -calls this action to call DoMyTriggeredEvent but this has parameter limitations. so call FOGTriggers.FogSteppedIntoArea(obj) aswell !???!!!
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ResetEvent, 1000, false );         // needed to reset
		FOGTriggers.FogSteppedIntoArea(obj,str,str2);   //calls this action aswell !!! needed to use playerbase ?!? (more parameters to be pushed)
		}					
    }

    void OnLeave(Object obj)
    {    
    }









};