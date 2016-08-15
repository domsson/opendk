#pragma once

namespace OpenDK
{

	enum CubeType
	{
		CUBE_UNDEFINED			= 0x0, // not present in original game
		EARTH_1					= 0x1,
		EARTH_2					= 0x2,
		EARTH_3					= 0x3,
		UNKNOWN_1				= 0x4,
		EARTH_4					= 0x5,
		UNKNOWN_2				= 0x6,
		UNKNOWN_3				= 0x7,
		UNKNOWN_4				= 0x8,
		UNKNOWN_5				= 0x9,
		UNKNOWN_6				= 0xa,
		UNKNOWN_7				= 0xb,
		UNKNOWN_8				= 0xc,
		PILLAR_PORTAL_1			= 0xd,
		PILLAR_PORTAL_2			= 0xe,
		PILLAR_PORTAL_3			= 0xf,
		LAIR_WALL_1				= 0x10,
		LAIR_WALL_2				= 0x11,
		LAIR_WALL_3				= 0x12,
		LAIR_WALL_4				= 0x13,
		LAIR_WALL_5				= 0x14,
		LAIR_WALL_6				= 0x15,
		LAIR_WALL_7				= 0x16,
		LAIR_WALL_8				= 0x17,
		EARTH_TORCH_PLATE		= 0x18,
		WALL_BOTTOM				= 0x19,
		PATH_1					= 0x1a,
		LAIR_BORDER_FLOOR_1		= 0x1e,
		LAIR_BORDER_FLOOR_2		= 0x1f,
		LAIR_BORDER_FLOOR_3		= 0x20,
		LAIR_BORDER_FLOOR_4		= 0x21,
		LAIR_BORDER_FLOOR_5		= 0x22,
		LAIR_BORDER_FLOOR_6		= 0x23,
		LAIR_BORDER_FLOOR_7		= 0x24,
		LAIR_BORDER_FLOOR_8		= 0x25,
		UNKNOWN_9				= 0x26,
		UNKNOWN_10				= 0x27,
		UNKNOWN_11				= 0x28,
		UNKNOWN_12				= 0x29,
		UNKNOWN_13				= 0x2a,
		ROCK_1					= 0x2b,
		ROCK_2					= 0x2c,
		ROCK_3					= 0x2d,
		UNKNOWN_14				= 0x2e,
		UNKNOWN_15				= 0x2f,
		UNKNOWN_16				= 0x30,
		GOLD_1					= 0x31,
		GOLD_2					= 0x32,
		GOLD_3					= 0x33,
		UNKNOWN_17				= 0x34,
		UNKNOWN_18				= 0x35,
		UNKNOWN_19				= 0x36,
		UNKNOWN_20				= 0x37,
		UNKNOWN_21				= 0x38,
		TREASURE_ROOM_PILLAR_1 	= 0x39,
		TREASURE_ROOM_PILLAR_2 	= 0x3a,
		UNKNOWN_22				= 0x3b,
		UNKNOWN_23				= 0x3c,
		UNKNOWN_24				= 0x3d,
		TREASURE_ROOM_PILLAR_3	= 0x3e,
		UNKNOWN_25				= 0x3f,
		UNKNOWN_26				= 0x40,
		TREASURE_ROOM_PILLAR_5	= 0x41,
		UNKNOWN_27				= 0x42,
		WALL_CENTRE_1			= 0x43,
		WALL_CENTRE_2			= 0x44,
		WALL_CENTRE_3			= 0x45,
		WALL_CENTRE_4			= 0x46,
		WALL_CENTRE_5			= 0x47,
		WALL_TORCH_PLACE		= 0x48,
		HEART_PEDESTAL_PILLAR_1	= 0x49,
		HEART_PEDESTAL_PILLAR_2	= 0x4a,
		UNKNOWN_28				= 0x4b,
		UNKNOWN_29				= 0x4c,
		WALL_BLANK_TOP_1		= 0x4d,
		WALL_BLANK_TOP_2		= 0x4e,
		WALL_STONE_1			= 0x4f,
		WALL_STONE_2			= 0x50,
		WALL_TRAIN_B_R			= 0x51,
		BRICK					= 0x52,
		WALL_TRAIN_B_L			= 0x53,
		WALL_WOMAN_1			= 0x54,
		WALL_WOMAN_2			= 0x55,
		WALL_WOMAN_3			= 0x56,
		WALL_WOMAN_4			= 0x57,
		WALL_WOMAN_5			= 0x58,
		WALL_WOMAN_6			= 0x59,
		WALL_WOMAN_7			= 0x5a,
		WALL_WOMAN_8			= 0x5b,
		WALL_WOMAN_9			= 0x5c,
		WALL_WOMAN_10			= 0x5d,
		WALL_WOMAN_11			= 0x5e,
		WALL_WOMAN_12			= 0x5f,
		WALL_TWIN_TOP_1			= 0x60,
		WALL_TWIN_TOP_2			= 0x61,
		WALL_TWIN_TOP_3			= 0x62,
		WALL_TWIN_TOP_4			= 0x63,
		WALL_TWIN_TOP_5			= 0x64,
		WALL_TWIN_TOP_6			= 0x65,
		WALL_TWIN_TOP_7			= 0x66,
		WALL_TWIN_TOP_8			= 0x67,
		WALL_TWIN_TOP_9			= 0x68,
		WALL_SHAGGING_1			= 0x69,
		WALL_SHAGGING_2			= 0x6a,
		WALL_SHAGGING_3			= 0x6b,
		WALL_SHAGGING_4			= 0x6c,
		WALL_SHAGGING_5			= 0x6d,
		WALL_SHAGGING_6			= 0x6e,
		WALL_SHAGGING_7			= 0x6f,
		WALL_SHAGGING_8			= 0x70,
		WALL_SHAGGING_9			= 0x71,
		WALL_SHAGGING_10		= 0x72,
		WALL_SHAGGING_11		= 0x73,
		WALL_SHAGGING_12		= 0x74,
		UNKNOWN_30				= 0x75,
		UNKNOWN_31				= 0x76,
		TORCH_PLATE				= 0x77,
		UNKNOWN_32				= 0x78,
		UNKNOWN_33				= 0x79,
		UNKNOWN_34				= 0x7a,
		UNKNOWN_35				= 0x7b,
		UNKNOWN_36				= 0x7c,
		UNKNOWN_37				= 0x7d,
		UNKNOWN_38				= 0x7e,
		UNKNOWN_39				= 0x7f,
		CLAIMED_NON_CENTRE		= 0x80,
		UNKNOWN_40				= 0x81,
		UNKNOWN_41				= 0x82,
		UNKNOWN_42				= 0x83,
		UNKNOWN_43				= 0x84,
		UNKNOWN_44				= 0x85,
		UNKNOWN_45				= 0x86,
		UNKNOWN_46				= 0x87,
		UNKNOWN_47				= 0x88,
		ROUND_PORTAL_CENTRE_1	= 0x89,
		ROUND_PORTAL_CENTRE_2	= 0x8a,
		ROUND_PORTAL_CENTRE_3	= 0x8b,
		ROUND_PORTAL_CENTRE_4	= 0x8c,
		ROUND_PORTAL_CENTRE_5	= 0x8d,
		ROUND_PORTAL_CENTRE_6	= 0x8e,
		ROUND_PORTAL_CENTRE_7	= 0x8f,
		ROUND_PORTAL_CENTRE_8	= 0x90,
		ROUND_PORTAL_CENTRE_9	= 0x91,
		WALL_CORNER_1			= 0x95,
		WALL_CORNER_2			= 0x96,
		WALL_CORNER_3			= 0x97,
		WALL_CORNER_4			= 0x98,
		WALL_TREASURE_MAIN_1	= 0x99,
		WALL_TREASURE_MAIN_2	= 0x9a,
		WALL_TREASURE_MAIN_3	= 0x9b,
		WALL_TREASURE_MAIN_4	= 0x9c,
		WALL_TREASURE_MAIN_5	= 0x9d,
		WALL_TREASURE_MAIN_6	= 0x9e,
		WALL_TREASURE_MAIN_7	= 0x9a,
		FLOOR_TREASURE_ROOM		= 0x9f,
		DRAPE_1					= 0xa0,
		DRAPE_2					= 0xa1,
		DRAPE_3					= 0xa2,
		UNKNOWN_48				= 0xa3,
		HEART_PEDESTAL_EDGE		= 0xa4,
		UNKNOWN_49				= 0xa5,
		UNKNOWN_50				= 0xa6,
		UNKNOWN_51				= 0xa7,
		WALL_LIBRARY_MAIN_1		= 0xa8,
		WALL_LIBRARY_MAIN_2		= 0xa9,
		WALL_LIBRARY_MAIN_3		= 0xaa,
		WALL_LIBRARY_MAIN_4		= 0xab,
		WALL_LIBRARY_MAIN_5		= 0xac,
		WALL_LIBRARY_MAIN_6		= 0xad,
		FLOOR_LIBRARY_1			= 0xae,
		FLOOR_LIBRARY_2			= 0xaf,
		LIBRARY_BOOKCASE_1		= 0xb0,
		LIBRARY_BOOKCASE_2		= 0xb1,
		LIBRARY_BOOKCASE_3		= 0xb2,
		LIBRARY_BOOKCASE_4		= 0xb3,
		LIBRARY_BOOKCASE_5		= 0xb4,
		LIBRARY_BOOKCASE_6		= 0xb5,
		UNKNOWN_52				= 0xb6,
		UNKNOWN_53				= 0xb7,
		UNKNOWN_54				= 0xb8,
		UNKNOWN_55				= 0xb9,
		UNKNOWN_56				= 0xba,
		UNKNOWN_57				= 0xbb,
		WALL_PRISON_CORNER_C_1	= 0xbc, // _C = centre
		WALL_PRISON_CORNER_C_2	= 0xbd, // _C = centre
		UNKNOWN_58				= 0xbe,
		UNKNOWN_59				= 0xbf,
		CLAIMED_CENTRE_P0		= 0xc0,
		CLAIMED_CENTRE_P1		= 0xc1,
		CLAIMED_CENTRE_P2		= 0xc2,
		CLAIMED_CENTRE_P3		= 0xc3,
		CLAIMED_CENTRE_P4		= 0xc7,
		FLOOR_PRISON_BORDERS_1	= 0xc8,
		FLOOR_PRISON_BORDERS_2	= 0xc9,
		FLOOR_PRISON_BORDERS_3	= 0xca,
		FLOOR_PRISON_BORDERS_4	= 0xcb,
		FLOOR_PRISON_BORDERS_5	= 0xcc,
		FLOOR_PRISON_BORDERS_6	= 0xcd,
		FLOOR_PRISON_BORDERS_7	= 0xce,
		FLOOR_PRISON_BORDERS_8	= 0xcf,
		FLOOR_PRISON_BORDERS_9	= 0xd0,
		UNKNOWN_60				= 0xd1,
		UNKNOWN_61				= 0xd2,
		UNKNOWN_62				= 0xd3,
		UNKNOWN_63				= 0xd4,
		UNKNOWN_64				= 0xd5,
		UNKNOWN_65				= 0xd6,
		UNKNOWN_66				= 0xd7,
		UNKNOWN_67				= 0xd8,
		UNKNOWN_68				= 0xd9,
		UNKNOWN_69				= 0xda,
		UNKNOWN_70				= 0xdb,
		HEART_PEDESTAL_CENTRE	= 0xdc,
		UNKNOWN_71				= 0xdd,
		UNKNOWN_72				= 0xde,
		UNKNOWN_73				= 0xdf,
		UNKNOWN_74				= 0xe0,
		WALL_PRISON_MAIN_1		= 0xe1,
		WALL_PRISON_MAIN_2		= 0xe2,
		WALL_PRISON_MAIN_3		= 0xe3,
		WALL_PRISON_MAIN_4		= 0xe4,
		WALL_PRISON_MAIN_5		= 0xe5,
		WALL_PRISON_MAIN_6		= 0xe6,

// TODO
/*

e8-f0	Torture wall main (2 layers)
f2-f7	Training wall main (top 2 layers)
f8	Unknown
f9-fa	Training wall pillar
fb	Training wall main (bottom middle)
fc	Training wall pillar
fd	Unknown
fe	Training border
ff-104	Workshop wall main (2 layers)
105-106	Unknown
107-109	Workshop non-centre
10a-10b	Unknown
10c-10e	Workshop wall corner centre
10f-114	Scavenger wall main (2 layers)
115	Unknown
116-118	Scavenger wall corner
119-11d	Unknown
11e	Temple wall corner
11f	Unknown
120	Temple wall corner
121	Dungeon heart part
122	Temple wall corner
123	Temple pool
124-125	Unknown
126-12e	Temple pool/magic door
12f-13a	Temple wall main
14b-14e	Library bookcase (ends)
14f-156	Hatchery wall main
157	Unknown
158	Hatchery wall corner centre
159	Hatchery pillar
15a	Hatchery border
15b	Hatchery wall corner centre
15c-162	Unknown
163-16b	Wooden door
16c-174	Braced door
175-17d	Iron door
17e-18d	Unknown
185-18d	Barracks main wall
18e-18f	Axe for barracks pillar
190	Centre of barracks corner column
191-1a8	Unknown
1a9	Centre of portal
1aa-1b1	Unknown
1b2	Graveyard wall right/left (middle layer)
1b3	Graveyard wall right/left (bottom layer)
1b4-1b8	Unknown
1b9	Gems
1ba	Gems
1bb	Gems
1bc	Gems
195-197	Twin wall (bottom layer of picture)
19a-1a5	Drapes (players 1-4)
*/
	};

}
