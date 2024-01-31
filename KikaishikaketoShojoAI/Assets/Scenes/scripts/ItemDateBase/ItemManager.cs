using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
public class ItemManager : MonoBehaviour {
 
	//　アイテムデータベース
	[SerializeField]
	private ItemDataBase itemDataBase;
    //　アイテム数管理
    //private Dictionary<Item, int> numOfItem = new Dictionary<Item, int>();
    [SerializeField]
    private static List<string> Item = new List<string>();

    private int ItemNum;
    // Use this for initialization
    private Image ItemImage;
    [SerializeField]
    private Text ItemName;
    [SerializeField]
    private Text ItemInfo;

    static bool item = false;
    
    void Start () {
        ItemNum = 0;

        ItemImage = this.GetComponent<Image>();
        ItemImage.sprite = GetItem(Item[ItemNum]).GetIcon();
        ItemName.text = GetItem(Item[ItemNum]).GetItemName();
        ItemInfo.text = GetItem(Item[ItemNum]).GetInformation();
        //item = false;

        //for (int i = 0; i < itemDataBase.GetItemLists().Count; i++) {
        //	//　アイテム数を適当に設定
        //	numOfItem.Add (itemDataBase.GetItemLists() [i], i);

        //	//　確認の為データ出力
        //	Debug.Log (itemDataBase.GetItemLists()[i].GetItemName() + ": " + itemDataBase.GetItemLists()[i].GetInformation());
        //}

        //Debug.Log (GetItem ("生ごみ").GetInformation());
        //Debug.Log (numOfItem [GetItem("生ごみ")]);
    }

    void Update()
    {
        if (Input.GetKeyDown("t") || Input.GetKeyDown("joystick button 5") && ItemNum < Item.Count)
        {
            ItemNum += 1;
        }

        if (Input.GetKeyDown("r") || Input.GetKeyDown("joystick button 4") && ItemNum > 0)
        {
            ItemNum -= 1;
        }

        if (Item.Count > 0)
        {
            ItemImage.sprite = GetItem(Item[ItemNum]).GetIcon();
            ItemName.text = GetItem(Item[ItemNum]).GetItemName();
            ItemInfo.text = GetItem(Item[ItemNum]).GetInformation();
        }
    }

    //　名前でアイテムを取得
    public Item GetItem(string searchName) {
		return itemDataBase.GetItemLists().Find(itemName => itemName.GetItemName() == searchName);
	}

    public void AddItem(string ItemName)
    {
        if (!Item.Contains(ItemName))
        {
            Item.Add(ItemName);
        }


    }

    public void HaveItem()
    {
        item = true;
    }

    public bool GethaveItem()
    {
        return item;
    }

    public void ResetHaveItem()
    {
        Item = new List<string>();
        item = false;
    }
}