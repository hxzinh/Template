// par[i] = x nếu viên sỏi i và viên sỏi x nằm trong cùng một hộp
// Nếu par[i] < 0 thì viên sỏi i nằm trong hộp i, và -par[i] chính là số sỏi trong hộp đó.
// Ban đầu, khởi tạo par[i] = -1 với mọi i.

int root(int v) {
    // Cho 1 số v, tìm hộp chứa viên sỏi v
    return par[v] < 0
            ? v
            : (par[v] = root(par[v])); // Viên sỏi v nằm trong cùng hộp với viên sỏi chứa par[v]
                                       // Chú ý ở đây ta gán lại par[v] = root(par[v]), kĩ thuật này
                                       // được gọi là Path Compression, giúp giảm độ phức tạp mỗi
                                       // thao tác xuống log(n)
}

void merge(int x, int y) {
    // Gộp 2 hộp chứa viên sỏi x và y vào cùng 1 hộp
    if ((x = root(x)) == (y = root(y)) {
        // 2 viên sỏi x và y đã thuộc cùng 1 hộp, ta không cần làm gì cả
        return ;
    }
    if (par[y] < par[x]) {
        // Ta gộp vào hộp chứa nhiều sỏi hơn. Kĩ thuật này gọi là Union-by-rank, và cũng giúp giảm
        // độ phức tạp mỗi thao tác xuống log(n).
        // Nếu kết hợp cả Union-by-rank và Path-compression thì độ phức tạp mỗi thao tác là ackerman(n),
        // rất rất nhỏ với n.
        swap(x, y);
    }
    par[x] += par[y];
    par[y] = x;
}