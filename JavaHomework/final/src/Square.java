import java.awt.Point;
import java.awt.Color;
public class Square {
	 private Point location;
	 private int[] key;
	 public Color color;
	 Square(Point l) {
		 location = l;
		 key = SquareKey.getRandomKey();
		 color=SquareKey.getColorByKey(key);
	 }

	 Square(Point l,int[] k) {
		 location = l;
		 key = k;
		 color=SquareKey.getColorByKey(k);
	 }
	 

	 public Point[] getShape()
	 {
		 return SquareKey.getShapeByKey(key);
	 }
	 
	 public Point[] getPaintLocation() {
		 Point[] s = SquareKey.getShapeByKey(key);
		 Point[] p = new Point[s.length];
		 for(int i=0;i<s.length;i++)
			 p[i] = new Point(s[i].x+location.x,s[i].y+location.y);
		 return p;
	 }	 

	 public Square getChangedSuqare(boolean isShapeChanged,int x,int y) {
		 Point l = new Point(this.location.x + x,this.location.y + y);
		 int[] k;
		 if(isShapeChanged)
			 k = SquareKey.getNextKey(this.key);
		 else
			 k = new int[]{this.key[0],this.key[1]};
		 return new Square(l,k);
	 }



}