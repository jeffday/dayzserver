//Vanilla Banov Init.c
// Thank you for using my map
void main()
{		
	//INIT WEATHER BEFORE ECONOMY INIT------------------------
	//Banov Init
	Weather weather = g_Game.GetWeather();

	weather.MissionWeather(false);    // false = use weather controller from Weather.c

	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);
	weather.GetRain().Set( 0, 0, 1);
	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);

	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
	
	//Loot spawn Creator
	//GetCEApi().ExportProxyData(vector.Zero, 100000); //Loot
	//GetCEApi().ExportClusterData(); //Fruit

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			int rndHlt = Math.RandomInt(55,100);
			itemEnt.SetHealth("","",rndHlt);
		}
	}

    void spawnItemsOnPlayer(PlayerBase player, TStringArray items) {
        for(int i = 0; i < items.Count(); i++) {
             player.GetInventory().CreateInInventory(items[i]);
        }
    }

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");//Creates random player
		Class.CastTo(m_player, playerEnt);

		GetGame().SelectPlayer(identity, m_player);

		return m_player;
	}

    void SpawnJeffSetup(PlayerBase player) {
        autoptr TStringArray clothes = {"beanie_blackred","ThickFramesGlasses","Hoodie_Sport1","SlacksPants_Khaki","SK8_Sneakers_Black"};

        spawnItemsOnPlayer(player, clothes);
    }

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			player.RemoveAllItems();
            
            SpawnJeffSetup(player);
            
            itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
			itemEnt = player.GetInventory().CreateInInventory( "Chemlight_White" );
            
            itemEnt = player.GetInventory().CreateInInventory( "CanOpener" );
            itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Cola" );
        	itemEnt = player.GetInventory().CreateInInventory( "SodaCan_Spite" );
            itemEnt = player.GetInventory().CreateInInventory( "BakedBeansCan" );
            itemEnt = player.GetInventory().CreateInInventory( "SpaghettiCan" );
		} 
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}