package com.company;

public class Hand {
    private int brick;
    private int grain;
    private int lumber;
    private int ore;
    private int wool;

    public Hand(){
        brick=0;
        grain=0;
        lumber=0;
        ore = 0;
        wool = 0;
    }

    public Resources.Resource loose_random_resource(){
        int rnd = (int)(Math.random()*(resource_cards()-1));
        int[] resources = get_resources_array();
        for(int i=0; i<5; i++){
            if(resources[i]>rnd){
                change_resource_counter(Resources.resource_array[i], -1);
                return Resources.resource_array[i];
            }
            else{
                rnd-=resources[i];
            }
        }
        return Resources.Resource.NONE;
    }

    int resource_cards() {
        return brick + grain + lumber + ore + wool;
    }

    boolean can_afford_road(){
        return (brick>=1 && lumber>=1);
    }

    boolean can_afford_settlement(){
        return (brick>=1 && lumber>=1 && wool>=1 && grain>=1);
    }

    boolean can_afford_city(){
        return (grain>=2 && ore>=3);
    }

    int[] get_resources_array(){
        int[] tab = new int[5];
        tab[0]=brick;
        tab[1]=lumber;
        tab[2]=wool;
        tab[3]=ore;
        tab[4]=grain;
        return tab;
    }

    void build_city(){
        ore-=3;
        grain-=2;
    }

    void build_settlement(){
        brick--;
        grain--;
        lumber--;
        wool--;
    }

    void build_road(){
        brick--;
        lumber--;
    }

    void change_resource_counter(Resources.Resource resource, int diff){
        switch (resource){
            case BRICK :
                brick+=diff;
                return;
            case LUMBER:
                lumber+=diff;
                return;
            case WOOL:
                wool+=diff;
                return;
            case ORE:
                ore+=diff;
                return;
            case GRAIN:
                grain+=diff;
                return;
            default:
                return;
        }
    }

    int get_number(Resources.Resource resource){
        switch (resource){
            case BRICK :
                return brick;
            case LUMBER :
                return lumber;
            case WOOL :
                return wool;
            case ORE :
                return ore;
            case GRAIN :
                return grain;
            default :
                return 0;
        }
    }
}
