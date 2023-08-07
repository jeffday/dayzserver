void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 4, reset_day = 30;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, 7, 0);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, 7, 0);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, 7, 0);
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
    
    EntityAI SpawnWithRandomHealth(PlayerBase player, string itemName)
    {
    	EntityAI itemEnt;
    
    	itemEnt = player.GetInventory().CreateInInventory(itemName);
        SetRandomHealth( itemEnt );
        
        return itemEnt;
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
    
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

    void SpawnJeffSetup(PlayerBase player) {
        autoptr TStringArray clothes = {"FP4_Hood_black","MMG_facemask_black","ThickFramesGlasses","MMG_combatshirt_black","MMG_combatpants_black","SK8_Sneakers_FullBlack","WoolGlovesFingerless_Black","Spur_MilBag_Black"};

        spawnItemsOnPlayer(player, clothes);

		autoptr TStringArray rifleAttachments = {"BO_LeupoldMk4", "BO_CorduraSuppressor_Black"};
		autoptr TStringArray beltAttachments = {"MMG_Holster_black","MMG_sheath_black","MMG_tactical_pouch_black","MMG_carbine_black"};
		autoptr TStringArray katanaAttachments = {"Katana"}; 


		spawnItemWithAttachments(player, "BO_M40A1", rifleAttachments);
		spawnItemWithAttachments(player, "KatanaSheath",katanaAttachments);

		EntityAI itemEnt;
        
        itemEnt = player.GetInventory().CreateInInventory("MMG_falcon_b1_belt_black");
		itemEnt.GetInventory().CreateAttachment("MMG_Holster_black");
		itemEnt.GetInventory().CreateAttachment("MMG_sheath_black");
		itemEnt.GetInventory().CreateAttachment("MMG_carbine_black");
		itemEnt = itemEnt.GetInventory().CreateAttachment("MMG_tactical_pouch_black");

		for(int i = 0; i < 12; i++) {
             itemEnt.GetInventory().CreateInInventory("AmmoBox_308Win_20Rnd");
        }
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
            itemEnt = player.GetInventory().CreateInInventory( "SpaghettiCan" );
		} 
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
