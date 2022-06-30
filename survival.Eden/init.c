void main()
{
	
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	
	//DATE RESET AFTER ECONOMY INIT-------------------------
	
	//GetCEApi().ExportProxyData("7500 0 7500", 20000);	// standard map groups (buildings) export, terrain center and radius needs to be specified
	//GetCEApi().ExportClusterData();					// cluster-type map groups export (fruit trees etc.)
	
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, 0);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, 0);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, 8, 0);
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
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		autoptr TStringArray torso = {"Shirt_Hawaiian1", "Shirt_Hawaiian2"};

		EntityAI itemEnt;
		ItemBase itemBs;

		int i = Math.RandomInt(0, torso.Count());

		player.RemoveAllItems();
		player.GetInventory().CreateInInventory(torso[i]);
		player.GetInventory().CreateInInventory("CanvasPants_Grey");
		player.GetInventory().CreateInInventory("AthleticShoes_Black");

		itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
		if ( Class.CastTo( itemBs, itemEnt ) )
			itemBs.SetQuantity( 2 );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}