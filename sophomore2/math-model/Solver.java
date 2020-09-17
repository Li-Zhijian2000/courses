import java.util.ArrayList;
import java.util.Collection;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;

/**
 * Solver
 */
public class Solver {

    private SearchNode currentNode;

    private int n;

    private int m;

    private int boatPersonNum;
    
    private boolean[][][] vis;
    
    private class SearchNode implements Comparable<SearchNode> {

        private int i;
        private int j;
        private int moves;

        private SearchNode preSearchNode;

        public final int priority;

        public SearchNode(int i, int j, SearchNode preSearchNode) {
            this.i = i;
            this.j = j;
            this.preSearchNode = preSearchNode;
            if (preSearchNode == null ) moves = 0;
            else moves = preSearchNode.moves + 1;
            priority = moves + n + m;
        }
        @Override
        public int compareTo(SearchNode b) {
            return Integer.compare(priority, b.priority);
        }

        public boolean isGoal() {
            return i == 0 && j == 0;
        }

        public Collection<SearchNode> neighbors(SearchNode preSearchNode) {
            Collection<SearchNode> neighbors = new ArrayList<>();
            
            final int[][] step;
            switch (boatPersonNum) {
                case 2: {
                    step = new int[][]{
                        {2, 0}, 
                        {1, 1}, {1, 0},
                        {0, 2}, {0, 1}};
                    break;
                }
                case 3: {
                    step = new int[][]{
                        {3, 0},
                        {2, 1}, {2, 0},
                        {1, 2}, {1, 1}, {1, 0},
                        {0, 3}, {0, 2}, {0, 1}
                    };
                    break;
                }
                default:
                    throw new IllegalArgumentException("the third args must be 2 or 3");
            }
             
            for (int k = 0; k < step.length; k++) {
                int si, sj;
                if (moves % 2 == 0) {
                    si = -step[k][0];
                    sj = -step[k][1];
                }
                else {
                    si = step[k][0];
                    sj = step[k][1];
                }
                int newi = i + si;
                int newj = j + sj;
                if (newi < 0 || newj < 0 || newi > n || newj > m) continue;
                if (newi == 0 || newi == n || newi == newj)
                    neighbors.add(new SearchNode(newi, newj, preSearchNode));
            }
            return neighbors;
        }
        
        @Override
        public boolean equals(Object o) {
            if (o == null) return false;
            if (o == this) return true;
            if (o.getClass().isInstance(this)) {
                SearchNode s = (SearchNode) o;
                if (i != s.i) return false;
                if (j != s.j) return false;
                return true;
            }
            return false;
        }   
        @Override   
        public String toString() {
            return i + " " + j;
        }
    }
    
    public Stack<SearchNode> solution() {
        if (currentNode.isGoal()) {
            Stack<SearchNode> solutions = new Stack<>();
            SearchNode node = currentNode;
            while (node != null) {
                solutions.push(node);
                node = node.preSearchNode;
            }
            return solutions;
        }
        return null;
    }
    
    public Solver(int n, int m, int boatPersonNum) {
        if (n < 0 || m < 0) {
            throw new IllegalArgumentException("n, m must greater or equal than 0");
        }
        if (n != m) {
            throw new IllegalArgumentException("n must equal to m");
        }
        this.n = n;
        this.m = m;
        this.boatPersonNum = boatPersonNum;
        this.vis = new boolean[n+1][m+1][2];

        currentNode = new SearchNode(n, m, null);

        Queue<SearchNode> pq = new PriorityQueue<>();
        pq.add(currentNode);

        while (true) {
            currentNode = pq.poll();

            if (currentNode == null) break;

            final int i = currentNode.i, j = currentNode.j, moves = currentNode.moves;
            if (vis[i][j][moves % 2]) continue;
            vis[currentNode.i][currentNode.j][currentNode.moves % 2] = true;
            
            if (currentNode.isGoal()) {
                break;
            }
            putNeiborsIntoPQ(currentNode, pq);
        }
    }

    public boolean isSolved() {
        return currentNode != null && currentNode.isGoal();
    }

    private void putNeiborsIntoPQ(SearchNode searchNode, Queue<SearchNode> pq) {
        Collection<SearchNode> neighbors = searchNode.neighbors(searchNode);
        for (SearchNode neighbor : neighbors) {
            if (!neighbor.equals(searchNode.preSearchNode)) {
                pq.add(neighbor);
            }
        }
    }
    private static void usage() {
        System.out.println("usage: java Solver num-of-businessman num-of-server num-of-boat-man");
    }

    public static void main(String[] args) {
        try {
            final int n = Integer.parseInt(args[0]);
            final int m = Integer.parseInt(args[1]);
            final int boatPersonNum = Integer.parseInt(args[2]);
    
            Solver solver = new Solver(n, m, boatPersonNum);
    
            if (!solver.isSolved()) {
                System.out.println("No solution possiple");
            }
            else {
                System.out.println("Minimum number of moves = " + solver.currentNode.moves);
                Stack<SearchNode> solutions = solver.solution();
                while (!solutions.empty()) {
                    SearchNode node = solutions.pop();
                    System.out.println(node);
                }
            }            
        } catch (IllegalArgumentException e) {
            System.out.println();
            usage();
            System.out.println();
            System.out.println("IllegalArguamentException: " + e.getMessage());
            System.out.println();
        }

    }
}