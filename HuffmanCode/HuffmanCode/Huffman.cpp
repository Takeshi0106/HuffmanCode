#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// ハフマン木のノード構造体
struct HuffmanNode {
	char ch; // 文字
	int freq; // 頻度
	HuffmanNode* left, * right; // 左右の子ノード

	HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// 優先度付きキューで使う比較関数（頻度が小さい順に並ぶようにする）
struct Compare {
	bool operator()(HuffmanNode* a, HuffmanNode* b) {
		return a->freq > b->freq; // 頻度の小さい方を優先（最小ヒープ）
	}
};

// 文字列と頻度マップからハフマン木を構築--------------------------------------------------------------------
HuffmanNode* buildHuffmanTree(const string& text, unordered_map<char, int>& freqMap) {
	priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

	// 頻度マップをもとに、各文字のノードを作成して優先度付きキューに追加


	// 木が一つになるまで、頻度の小さい2つのノードを取り出して統合
	while (pq.size() > 1) {


		// 新しい親ノードを作成し、左右の子ノードを設定


		// 親ノードを再びキューに追加

	}

	// 最後に残ったノードが木の根となる
	return pq.top();
}
// 文字列と頻度マップからハフマン木を構築--------------------------------------------------------------------

// ハフマン木から文字ごとの符号を再帰的に生成
void buildCodes(HuffmanNode* node, string code, unordered_map<char, string>& huffmanCode) {
	if (!node) return;

	// 葉ノードに到達したら、符号をマップに登録
	if (node->ch != '\0') {
		huffmanCode[node->ch] = code;
	}

	// 左の枝は"0"を追加、右の枝は"1"を追加して再帰呼び出し
	buildCodes(node->left, code + "0", huffmanCode);
	buildCodes(node->right, code + "1", huffmanCode);
}

// テキストをハフマン符号に基づいて符号化
string encode(const string& text, unordered_map<char, string>& huffmanCode) {
	string encoded = "";
	for (char ch : text) {
		encoded += huffmanCode[ch]; // 各文字を対応するビット列に置換
	}
	return encoded;
}

// ハフマン符号列を元の文字列に復号化
string decode(const string& encoded, HuffmanNode* root) {
	string decoded = "";
	HuffmanNode* node = root;

	// 1ビットずつ読みながら木をたどって復号
	for (char bit : encoded) {
		if (bit == '0') node = node->left;
		else node = node->right;

		// 葉ノードに到達したら、対応する文字を追加して木の根に戻る
		if (node->ch != '\0') {
			decoded += node->ch;
			node = root;
		}
	}

	return decoded;
}

// メイン関数
int main() {
	// 入力テキスト
	string text = "this is an example for huffman encoding";

	// 各文字の出現頻度を計算
	unordered_map<char, int> freqMap;
	for (char ch : text) freqMap[ch]++;
	cout << "出現頻度:\n";
	for (auto map :freqMap){
		cout << map.first << ":" << map.second <<"\n";
	}

	// ハフマン木を構築
	HuffmanNode* root = buildHuffmanTree(text, freqMap);

	// ハフマン符号を生成
	unordered_map<char, string> huffmanCode;
	buildCodes(root, "", huffmanCode);

	// 符号の表示
	cout << "Huffman Codes:\n";
	for (auto pair : huffmanCode) {
		cout << pair.first << ": " << pair.second << '\n';
	}

	// テキストを符号化
	string encoded = encode(text, huffmanCode);
	cout << "\nEncoded:\n" << encoded << "\n";

	// 符号列を復号化
	string decoded = decode(encoded, root);
	cout << "\nDecoded:\n" << decoded << "\n";

	return 0;
}
