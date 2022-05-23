void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();				

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
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

const string TOURIST = "tourist";
const string RURAL = "rural";
const string VILLAGER = "villager";
const string TOWNSPERSON = "townsperson";
const string CITYPERSON = "cityperson";

const string PLAYER_CLASSES[] = {TOURIST, RURAL, VILLAGER, TOWNSPERSON, CITYPERSON};

// HEAD CLOTHING OPTIONS:
autoptr TStringArray FLAT_CAPS = {"FlatCap_Black", "FlatCap_BlackCheck", "FlatCap_Blue", "FlatCap_Brown", "FlatCap_BrownCheck", "FlatCap_Grey", "FlatCap_GreyCheck", "FlatCap_Red"};
autoptr TStringArray RADAR_CAPS = {"RadarCap_Black", "RadarCap_Blue", "RadarCap_Brown", "RadarCap_Green", "RadarCap_Red"};

// TORSO CLOTHING OPTIONS:
autoptr TStringArray TSHIRTS = {"TShirt_Beige", "TShirt_Black", "TShirt_Blue", "TShirt_Green", "TShirt_Grey", "TShirt_OrangeWhiteStripes", "TShirt_Red", "TShirt_RedBlackStripes", "TShirt_White"};
autoptr TStringArray RAGLAN_SHIRTS = {"Medium_Sleeves_Shirt", "Medium_Sleeves_Shirt_Red", "Medium_Sleeves_Shirt_Blue"}; // WINDSTRIDE
autoptr TStringArray LAYERED_SHIRTS = {"Layered_Shirt_Base", "Layered_Shirt_White", "Layered_Shirt_Cheburashka", "Layered_Shirt_Courage", "Layered_Shirt_Lily"}; // WINDSTRIDE
autoptr TStringArray QUILTED_JACKETS = {"QuiltedJacket_Black", "QuiltedJacket_Blue", "QuiltedJacket_Green", "QuiltedJacket_Grey", "QuiltedJacket_Orange", "QuiltedJacket_Red", "QuiltedJacket_Violet", "QuiltedJacket_Yellow"};
autoptr TStringArray TRACK_JACKETS = {"TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LightBlue","TrackSuitJacket_Red"};

// LEGS CLOTHING OPTIONS:
autoptr TStringArray TRACK_PANTS = {"TrackSuitPants_Black", "TrackSuitPants_Blue", "TrackSuitPants_Green", "TrackSuitPants_LightBlue", "TrackSuitPants_Red"};
autoptr TStringArray HIKING_PANTS = {"CanvasPants_Beige", "CanvasPants_Blue", "CanvasPants_Grey", "CanvasPants_Red", "CanvasPants_Violet"};
autoptr TStringArray JEANS = {"Jeans_Black","Jeans_Blue","Jeans_BlueDark","Jeans_Brown","Jeans_Green","Jeans_Grey"};

// FEET CLOTHING OPTIONS:
autoptr TStringArray RUNNING_SHOES = {"JoggingShoes_Black", "JoggingShoes_Blue", "JoggingShoes_Red", "JoggingShoes_Violet", "JoggingShoes_White"};
autoptr TStringArray SKATE_SHOES = {"SK8_Sneakers_Black", "SK8_Sneakers_FullBlack", "SK8_Sneakers_Blue"}; // WINDSTRIDE
autoptr TStringArray WELLIES = {"Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey"};
const string FLIP_FLOPS = "FlipFlops_Colorbase";

// BAG OPTIONS:
autoptr TStringArray CANVAS_BACKPACKS = {"Canvas_Backpack_Base", "Canvas_Backpack_Black", "Canvas_Backpack_White", "Canvas_Backpack_Red", "Canvas_Backpack_Blue", "Canvas_Backpack_Purple"}; // WINDSTRIDE
autoptr TStringArray LONE_WANDERER_BACKPACKS = {"Spur_LW_Bag_Black", "Spur_LW_Bag_Blue", "Spur_LW_Bag_Brown", "Spur_LW_Bag_Green", "Spur_LW_Bag_Grey", "Spur_LW_Bag_Orange", "Spur_LW_Bag_Purple", "Spur_LW_Bag_Red"}; // SPURGLES

class CustomMission: MissionServer
{
    string randomElement(TStringArray arr) {
        int i = Math.RandomInt(0, arr.Count());

        return arr[i];
    }

	void setRandomHealth(EntityAI itemEnt)
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

    void spawnItemsOnPlayer(PlayerBase player, TStringArray items, bool withDamage) {
        for(int i = 0; i < items.Count(); i++) {
             EntityAI itemEnt = player.GetInventory().CreateInInventory(items[i]);

            if(withDamage) {
                setRandomHealth(itemEnt);
            }
        }
    }

    void spawnItemWithAttachments(PlayerBase player, string parentItem, TStringArray attachments) {
        EntityAI itemEnt;
        
        itemEnt = player.GetInventory().CreateInInventory(parentItem);

        for(int i = 0; i < attachments.Count(); i++) {
            itemEnt.GetInventory().CreateAttachment(attachments[i]);
        }   
    }

    string pickPlayerClass() {
        int i = Math.RandomInt(0, 5);

        return PLAYER_CLASSES[i];
    }

    // spawns with some food and a bag but bad clothes
    void spawnTourist(PlayerBase player) {

        string torso = randomElement(TSHIRTS);
        string legs = randomElement(JEANS);
        string feet = randomElement(RUNNING_SHOES);
        string bag = randomElement(CANVAS_BACKPACKS);

        autoptr TStringArray playerItems = {torso, legs, feet, bag};

        spawnItemsOnPlayer(player, playerItems, true);

        player.GetInventory().CreateInInventory("ZagorkyChocolate");
        player.GetInventory().CreateInInventory("WaterBottle");
    }

    // spawns with warm clothes and a bladed weapon
    void spawnRural(PlayerBase player) {
        autoptr TStringArray bladedTools = {"CrudeMachete", "Machete", "Hatchet"};

        string torso = randomElement(QUILTED_JACKETS);
        string legs = randomElement(HIKING_PANTS);
        string feet = randomElement(WELLIES);
        string tool = randomElement(bladedTools);

        autoptr TStringArray playerItems = {torso, legs, feet, tool};

        spawnItemsOnPlayer(player, playerItems, true);
    }

    // spawns with crappy clothes but a lighter and a knife
    void spawnVillager(PlayerBase player) {
        // explicit random selection here so we can make track suit consistent
        int i = Math.RandomInt(0, 5);
        string torso = TRACK_JACKETS[i];
        string legs = TRACK_PANTS[i];

        string head = randomElement(FLAT_CAPS);
        string feet = FLIP_FLOPS;

        autoptr TStringArray playerItems = {torso, legs, feet, head};

        spawnItemsOnPlayer(player, playerItems, true);

        player.GetInventory().CreateInInventory("PetrolLighter");
        player.GetInventory().CreateInInventory("HuntingKnife");
        player.GetInventory().CreateInInventory("SodaCan_Kvass");
    }

    // spawns with mediocre clothes and no food but with a very good bag
    void spawnTownsperson(PlayerBase player) {
        string torso = randomElement(LAYERED_SHIRTS);
        string legs = randomElement(JEANS);
        string head = randomElement(RADAR_CAPS);
        string feet = randomElement(SKATE_SHOES);

        string bag = randomElement(LONE_WANDERER_BACKPACKS);

        autoptr TStringArray playerItems = {torso, legs, head, feet, bag};

        spawnItemsOnPlayer(player, playerItems, true);
    }

    // void spawnCityperson(PlayerBase player) {

    // }

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
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );

		if ( itemClothing )
		{
			player.RemoveAllItems();
            
            string playerClass = pickPlayerClass();

            switch(playerClass){
                case TOURIST:
                    spawnTourist(player);
                    break;
                case RURAL:
                    spawnRural(player);
                    break;
                case VILLAGER:
                    spawnVillager(player);
                    break;
                case TOWNSPERSON:
                    spawnTownsperson(player);
                    break;
                case CITYPERSON:
                    spawnVillager(player);
                    break;
            }

            // Universal items

			itemEnt = player.GetInventory().CreateInInventory( "BandageDressing" );
		}
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}