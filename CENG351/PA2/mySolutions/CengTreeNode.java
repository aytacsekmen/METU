import java.awt.Color;
import java.util.ArrayList;

public abstract class CengTreeNode
{
    static protected Integer order;
    private CengTreeNode parent;
    protected CengNodeType type;

    public Integer level;
    public Color color;


    public CengTreeNode(CengTreeNode parent)
    {
        this.parent = parent;
        this.color = CengGUI.getRandomBorderColor();
    }
    public CengTreeNode getParent()
    {
        return parent;
    }

    public void setParent(CengTreeNode parent)
    {
        this.parent = parent;
    }

    public CengNodeType getType()
    {
        return type;
    }
    public Color getColor()
    {
        return this.color;
    }
    public void btree_printer( Integer node_level)
    {
        //ne kadar tab atmam gerektiğini dolduruyorum
        String tab_sayisi = "\t".repeat(node_level);

        //eger gelen node leaf ise leaf nodeu olarak yazılır
        if(this.getType() == CengNodeType.Leaf){

            CengTreeNodeLeaf tmp = ((CengTreeNodeLeaf) this);
            System.out.println(tab_sayisi + "<data>");

            for(int i = 0; i < tmp.bookCount(); i++) {
                System.out.println(tab_sayisi + "<record>" + tmp.getBook(i).fullName() + "</record>");
            }

            System.out.println(tab_sayisi + "</data>");

        }
        //eger gelen node internal node ise internal nodeu olarak yazılır
        else
        {
            CengTreeNodeInternal tmp = ((CengTreeNodeInternal) this);
            Integer key_count = tmp.keyCount();
            //gerekli şeyleri printliyorum
            System.out.println(tab_sayisi + "<index>");
            for(int i = 0; i < key_count; i++)
                System.out.println(tab_sayisi + tmp.keyAtIndex(i));
            System.out.println(tab_sayisi + "</index>");

            for(int i = 0; i <= key_count; i++)
            {
                tmp.getChild(i).btree_printer( node_level+1);
            }

        }
    }

}
