void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 8, reset_day = 10;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
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

	void spawnItemNTimesOnPlayer(PlayerBase player, string item, int n) {
        for(int i = 0; i < n; i++) {
            player.GetInventory().CreateInInventory(item);
        }
    }

    void spawnItemsOnPlayer(PlayerBase player, TStringArray items) {
        for(int i = 0; i < items.Count(); i++) {
             player.GetInventory().CreateInInventory(items[i]);
        }
    }

    void spawnItemWithAttachments(PlayerBase player, string parentItem, TStringArray attachments) {
        EntityAI itemEnt;
        
        itemEnt = player.GetInventory().CreateInInventory(parentItem);

        for(int i = 0; i < attachments.Count(); i++) {
            itemEnt.GetInventory().CreateAttachment(attachments[i]);
        }   
    }

    // god dammit moitzbert
    string getItemNameForCamoType(string prefix, string camoType)
    {
        if (camoType == "green")
        {
            if(prefix == "MMG_Mag_Pouch_" || prefix == "MMG_JPC_Vest_" || prefix == "MMG_ammo_pouch_" || prefix == "MMG_Med_Pouch_" || prefix == "MMG_carrier_backpack_" || prefix == "MMG_assault_pack_" || prefix == "MMG_falcon_b1_belt_" || prefix == "MMG_sheath_" || prefix == "MMG_bottle_" || prefix == "MMG_combatpants_" || prefix == "MMG_balaclava_") {
                return prefix + "olive";
            }
        }

        return prefix + camoType;
    }

    // yet another special case
    void spawnHeadphones(PlayerBase player, string camoType)
    {
        switch(camoType) { 
            case "multicam":
            case "ucp":
            case "green":
            case "erdl":
            case "multicam_tropic":
            case "ukraine":
            case "germany":
            case "sweden":
            case "norway":
                player.GetInventory().CreateInInventory("MMG_headphones_green");
                break;
            case "black":
            case "dark_woodland":
            case "multicamblack":
                player.GetInventory().CreateInInventory("MMG_headphones_black");
                break;
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