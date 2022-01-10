var races_dict = new Object();

races_dict = {
    'human': 'Recent discoveries have shown that humans are descended from the barbaric vrykul, half-giant warriors who live in Northrend. Early humans were primarily a scattered and tribal people for several millennia, until the rising strength of the troll empire forced their strategic unification. Thus the nation of Arathor was formed, along with its capital, the city-state of Strom.',
    'dwarf': 'The bold and courageous dwarves are an ancient race descended from the earthen—beings of living stone created by the titans when the world was young. Due to a strange malady known as the Curse of Flesh, the dwarves’ earthen progenitors underwent a transformation that turned their rocky hides into soft skin. Ultimately, these creatures of flesh and blood dubbed themselves dwarves and carved out the mighty city of Ironforge in the snowy peaks of Khaz Modan.',
    'night elf': "The ancient and reclusive night elves have played a pivotal role in shaping Azeroth’s fate. The night elves of today still remember the War of the Ancients over ten thousand years ago, when they halted the Burning Legion’s first invasion of Azeroth. When the Legion’s remnants rallied together with the vile satyrs centuries later, the night elves again opposed the threat, ultimately vanquishing the forces that set out to wreak havoc on their world. ",
    'gnome': "The clever, spunky, and oftentimes eccentric gnomes present a unique paradox among the civilized races of Azeroth. Brilliant inventors with an irrepressibly cheerful disposition, this race has suffered treachery, displacement, and near-genocide. It is their remarkable optimism in the face of such calamity that symbolizes the truly unshakable spirit of the gnomes.",
    'draenei': "Long before the fallen titan Sargeras unleashed the Legion on Azeroth, he conquered the world of Argus and its inhabitants, the eredar. Believing that this gifted race would be crucial in his quest to undo all of creation, Sargeras contacted the eredar’s leaders – Kil’jaeden, Archimonde, and Velen, offering them knowledge and power in exchange for their loyalty.",
    'worgen': "Behind the formidable Greymane Wall, a terrible curse transformed some of the stalwart citizens of the isolated kingdom of Gilneas into nightmarish lupine beasts known as worgen. Human scholars intensely debated the origins of the curse, until it was revealed that the original worgen were not—as previously believed—nightmares from another dimension, but cursed night elf druids.",
    'orc': "Unlike the other races of the Horde, orcs are not native to Azeroth. Initially, they lived as shamanic clans on the lush world of Draenor. They abandoned their peaceful culture when Kil’jaeden, a demon lord of the Burning Legion, corrupted the orcs and used them in his vengeful plot against the draenei, who were exiles from Kil’jaeden’s homeworld.",
    'undead': "Death offered no escape for the scores of humans killed during the Lich King’s campaign to scour the living from Lordaeron. Instead, the kingdom’s fallen were risen into undeath as Scourge minions and forced to wage an unholy war against everything… and everyone… that they once held dear.",
    'tauren': "The peaceful tauren—known in their own tongue as the shu’halo—have long dwelled in Kalimdor, striving to preserve the balance of nature at the behest of their goddess, the Earth Mother. Until recently, the tauren lived as nomads scattered throughout the Barrens, hunting the great kodo beasts native to the arid region.",
    'troll': "The savage trolls of Azeroth are infamous for their cruelty, dark mysticism, and seething hatred for all other races. Yet one exception among the trolls is the Darkspear tribe. Plagued by a history of subservience and exile, this proud tribe was on the brink of extinction when Warchief Thrall and his mighty Horde forces were driven to the trolls’ remote island home in the South Seas during a violent storm.",
    'blood elf': "For nearly 7,000 years, high elven society centered on the sacred Sunwell, a magical fount that was created using a vial of pure arcane energy from the first Well of Eternity. Nourished and strengthened by the Sunwell’s potent energies, the high elves’ enchanted kingdom of Quel’Thalas prospered within the verdant forests north of Lordaeron.",
    'goblin': "Originally the slaves of jungle trolls on the Isle of Kezan, goblins were forced to mine kaja’mite ore out of the volcanic bowels of Mount Kajaro. The trolls used this potent mineral for their voodoo rituals, but it had an unexpected effect on the slaves who were in constant contact with it: kaja’mite generated new cunning and intelligence in the goblin race.",
    'pandaren': "Couched in myth and legend, rarely seen and even more rarely understood, the enigmatic pandaren have long been a mystery to the other races of Azeroth. The noble history of the pandaren people stretches back thousands of years, well before the empires of man and before even the sundering of the world."
}

var race_logo = document.getElementById("race-logo");
var race_image = document.getElementById('race-image');
var race_shower = document.getElementById('race-shower');
var fractions = document.getElementById('fractions');
var list_items = fractions.getElementsByTagName('li');

function displayRaceData(el) {
    var race = new String(el.innerHTML);
    console.log(el);
    if (/\s/.test(race)) {
        img = race.split(' ').join('_').toLowerCase() + ".png";
    }
    else {
        img = race.toLowerCase() + ".png";
    }
    logo_img = "./pics/races_symbol/" + img;
    race_img = "./pics/races/" + img;


    race_shower.childNodes[1].style.backgroundColor = 'rgba(255, 255, 255, 0.60)';
    race_shower.childNodes[3].style.backgroundColor = 'rgba(255, 255, 255, 0.60)';

    race_shower.childNodes[1].innerHTML = race;
    race_shower.childNodes[3].innerHTML = races_dict[race.toLowerCase()];

    race_image.style.backgroundImage = "url(" + race_img + ")";
    race_logo.style.backgroundImage = "url(" + logo_img + ")";
}


for (var i = 0, li_size = list_items.length; i < li_size; i++)
{
    list_items[i].addEventListener("click", function() { displayRaceData(this); }, true);
}
