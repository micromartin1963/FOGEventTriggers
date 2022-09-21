class FOG_MYTrigger extends Trigger
{
	protected int m_fogtrigger;
	protected ref EffectSound m_fogtriggerSound;
	
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
	

		

		
	void OnEnter(Object obj)
    {
	vector WhereIsIt = "10810 4 2266";
            PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());


		if (vector.Distance(this.GetPosition(), WhereIsIt) <= 20.0)
		{
		TriggerOnEnterEvent(1);    // -------------------
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLater( ResetEvent, 1000, false );
		}					
    }

    void OnLeave(Object obj)
    {    
    }
};