#define _ARMA_

class CfgPatches
{
	class FOGTriggers
	{
		units[] = {"FOGNPC_SurvivorM_Mirek"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Sounds_Effects","DZ_Scripts","DZ_Characters","JM_CF_Scripts"};
	};
};
class CfgMods
{
	class FOG_NPC
	{
		dir = "FOG";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "FOGTriggers";
		credits = "Hunterz";
		authorID = "0";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"FOG/FOGTriggers/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"FOG/FOGTriggers/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FOG/FOGTriggers/Scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{
	class SurvivorBase;

        class SurvivorF_Irena;
	class FOGNPCBase: SurvivorF_Irena
	{
		scope = 0;

	};


	class FOGNPC_SurvivorM_Mirek: FOGNPCBase
	{
		scope = 2;

	};


};




class CfgSoundShaders
{
	class baseCharacter_SoundShader;

	class FOG_SoundShader1: baseCharacter_SoundShader
	{
		samples[] = {{"FOG\FOGTriggers\sounds\attack_1",1}};
		volume = 1;
		range = 60;
		rangeCurve[] = {{0,1},{0.5,0.7},{1,0}};
	};

};



class CfgSoundSets
{
	//class baseCharacter_SoundSet;
	class FOG_SoundSet_001
	{
		soundShaders[] = {"FOG_SoundShader1"};
	};
};

