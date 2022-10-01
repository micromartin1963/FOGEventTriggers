


class FOGInfo
{
    string LocationName;
    int TType;
    string FogText;
    string OrigVectorStr;
    string TargetVectorStr;
    string FogRadius;
    string FogClassnameStr;
    int FogSoundIndex;
 


    void FOGInfo(string loc,int Type,string nam,string v,string v2,string rad,string cn,int index) 
	{
	LocationName = loc;
	TType = Type;
        FogText = nam;
	OrigVectorStr = v;
	TargetVectorStr = v2;
	FogRadius = rad;
	FogClassnameStr = cn;
	FogSoundIndex = index;
	}
}


class FOG__Info
{
	ref array< ref FOGInfo > FOGLocs;	
	void FOG__Info()
	{
	FOGLocs = new ref array< ref FOGInfo >;
	}
}


class FOGTriggerConfig
{

    protected const static string m_CfgRoot = "$profile:\\FOGTriggers\\";

    static void LoadConfig(string cfgName, out FOG__Info configData)
    {
        string configPath = m_CfgRoot + cfgName;

        if (!FileExist(configPath))    //------------------------------------ we need a logger to do this properly
        {
	// --------------------------------------------------put an error message up and log todo
	Print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX not found FODERROR");
        }
	else
	{
	Print("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX found FODNOERROR");
	}

        JsonFileLoader<FOG__Info>.JsonLoadFile(configPath, configData);

    }


}
