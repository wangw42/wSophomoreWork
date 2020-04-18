import java.awt.Point;
import java.awt.Color;
import java.util.Random;


public class SquareKey {

	private static final Point[] a1 = new Point[] {new Point(0,0),new Point(1,0),new Point(0,1),new Point(1,1)};
	private static final Point[][] a = new Point[][]{a1,a1,a1,a1};
	
	private static final Point[] b1 = new Point[] {new Point(0,0),new Point(0,1),new Point(0,2),new Point(0,3)};
	private static final Point[] b2 = new Point[] {new Point(0,0),new Point(1,0),new Point(2,0),new Point(3,0)};
	private static final Point[][] b = new Point[][]{b1,b2,b1,b2};
	
	private static final Point[] c1 = new Point[] {new Point(0,0),new Point(0,1),new Point(0,2),new Point(1,1)};
	private static final Point[] c2 = new Point[] {new Point(0,1),new Point(1,1),new Point(2,1),new Point(1,0)};
	private static final Point[] c3 = new Point[] {new Point(1,0),new Point(1,1),new Point(1,2),new Point(0,1)};
	private static final Point[] c4 = new Point[] {new Point(0,0),new Point(1,0),new Point(2,0),new Point(1,1)};
	private static final Point[][] c = new Point[][]{c1,c2,c3,c4};
	
	private static final Point[] d1 = new Point[] {new Point(0,0),new Point(1,0),new Point(1,1),new Point(2,1)};
	private static final Point[] d2 = new Point[] {new Point(1,0),new Point(1,1),new Point(0,1),new Point(0,2)};
	private static final Point[][] d = new Point[][]{d1,d2,d1,d2};
	
	private static final Point[] e1 = new Point[] {new Point(0,1),new Point(1,1),new Point(1,0),new Point(2,0)};
	private static final Point[] e2 = new Point[] {new Point(0,0),new Point(0,1),new Point(1,1),new Point(1,2)};
	private static final Point[][] e = new Point[][]{e1,e2,e1,e2};
	
	private static final Point[] f1 = new Point[] {new Point(0,0),new Point(0,1),new Point(0,2),new Point(1,2)};
	private static final Point[] f2 = new Point[] {new Point(0,1),new Point(1,1),new Point(2,1),new Point(2,0)};
	private static final Point[] f3 = new Point[] {new Point(0,0),new Point(1,0),new Point(1,1),new Point(1,2)};
	private static final Point[] f4 = new Point[] {new Point(0,1),new Point(0,0),new Point(1,0),new Point(2,0)};
	private static final Point[][] f = new Point[][]{f1,f2,f3,f4};
	
	private static final Point[] g1 = new Point[] {new Point(0,0),new Point(1,0),new Point(2,0),new Point(2,1)};
	private static final Point[] g2 = new Point[] {new Point(0,2),new Point(0,1),new Point(0,0),new Point(1,0)};
	private static final Point[] g3 = new Point[] {new Point(0,0),new Point(0,1),new Point(1,1),new Point(2,1)};
	private static final Point[] g4 = new Point[] {new Point(0,2),new Point(1,2),new Point(1,1),new Point(1,0)};
	private static final Point[][] g = new Point[][]{g1,g2,g3,g4};
	
	
	public static Color randomColor() {
		Random random = new Random();
		int r = random.nextInt(256);
		int g = random.nextInt(256);
		int b = random.nextInt(256);
		return new Color(r, g, b);
	}

	private static final Point[][][] shapelist = new Point[][][]{a,b,c,d,e,f,g};
	private static final Color[] colorlist = {randomColor(),randomColor(),randomColor(),randomColor(),randomColor(),randomColor(),randomColor()};
	

	public static Point[] getShapeByKey(int[] key)
	{
		return shapelist[key[0]][key[1]];
	}

	public static Color getColorByKey(int[] key)
	{
		return colorlist[key[0]];
	}

	public static int[] getRandomKey() {
		Random r = new Random();
		int i = r.nextInt(shapelist.length);
		int j = r.nextInt(shapelist[i].length);
		return new int[]{i,j};
	}
	

	public static int[] getNextKey(int[] key)
	{
		return new int[]{key[0],(key[1]+1)%shapelist[key[0]].length};
	}
}
