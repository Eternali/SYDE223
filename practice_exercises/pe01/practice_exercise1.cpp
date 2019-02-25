// Conrad Heidebrecht 20710386   

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Artwork {

private:
    string _artistName;
    unsigned int _year;
    string _title;

public:
    string getArtist() { return _artistName; }

    Artwork() {
        _year = 0;
    }
    Artwork(string name, unsigned int year, string title) : _artistName(name), _year(year), _title(title) {
    
    }

    friend bool operator==(const Artwork& left, const Artwork& right) {
        return left._artistName == right._artistName && left._year == right._year && left._title == right._title;
    }

};

class SoldArtwork : public Artwork {
    
private:
    string _customerName;
    string _customerAddr;
    double _saleAmount;

public:
    SoldArtwork() {
        _saleAmount = 0.0;
    }
    SoldArtwork(
        string name,
        unsigned int year,
        string title,
        string customerName,
        string customerAddr,
        double saleAmount
    ) : Artwork(name, year, title), _customerName(customerName), _customerAddr(customerAddr), _saleAmount(saleAmount) {
        
    }

    friend bool operator==(const SoldArtwork& left, const SoldArtwork& right) {
        return left._customerName == right._customerName &&
            left._customerAddr == right._customerAddr &&
            left._saleAmount == right._saleAmount
            && static_cast<Artwork>(left) == static_cast<Artwork>(right);
    }

};

class ArtworkCollection {

public:
    vector<Artwork> artworks;
    vector<SoldArtwork> soldArtworks;

    bool insert_artwork(const Artwork& artwork_info) {
        if (find(artworks.begin(), artworks.end(), artwork_info) != artworks.end()) {
            return false;
        }
        artworks.push_back(artwork_info);
        return true;
    }

    bool sell_artwork(const SoldArtwork& artwork_info) {
        vector<Artwork>::iterator index = find(artworks.begin(), artworks.end(), static_cast<Artwork>(artwork_info));
        if (index != artworks.end()) {
            artworks.erase(index);
            soldArtworks.push_back(artwork_info);
            return true;
        }
        return false;
    }

    bool operator==(const ArtworkCollection& other) {
        return artworks == other.artworks && soldArtworks == other.soldArtworks;
    }

    friend ArtworkCollection operator+(const ArtworkCollection& left, const ArtworkCollection& right) {
        // because we're not allowed to make explicit constructors we have to set each vector individually
        ArtworkCollection combined = ArtworkCollection();

        combined.artworks = left.artworks;
        combined.artworks.insert(combined.artworks.end(), right.artworks.begin(), right.artworks.end());

        combined.soldArtworks = left.soldArtworks;
        combined.soldArtworks.insert(combined.soldArtworks.end(), right.soldArtworks.begin(), right.soldArtworks.end());

        return combined;
    }

};

//// Tests ////

ArtworkCollection generate_test_data() {
    ArtworkCollection data = ArtworkCollection();

    data.artworks = {
        Artwork("John Smith", 2001, "A dog"),
        Artwork("Jane Doe", 2010, "A cat"),
        Artwork("Alice Brown", 2011, "A lizard")
    };
    data.soldArtworks = {
        SoldArtwork("Jane Doe", 2019, "The cat", "John Smith", "123 Boring Street", 16000.00),
    };

    return data;
}

bool assert(bool expr, string msg) {
    if (!expr) cout << "FAILED: ";
    cout << msg << endl;
    return expr;
}

bool test_insert_artwork() {
    ArtworkCollection collection = ArtworkCollection();
    Artwork baseArt = Artwork("John Smith", 2001, "A dog");
    
    // test valid insert
    bool result = collection.insert_artwork(baseArt);
    bool passed = assert(result && collection.artworks == vector<Artwork>({ baseArt }), "Can insert valid artwork.");

    // test inserting same artwork again
    result = collection.insert_artwork(baseArt);
    passed = assert(!result && collection.artworks == vector<Artwork>({ baseArt }), "Cannot insert duplicate artwork.");

    return passed;
}

bool test_sell_artwork() {
    ArtworkCollection collection = ArtworkCollection();
    Artwork baseArt = Artwork("Jane Doe", 2011, "A lizard");
    SoldArtwork soldArt = SoldArtwork("Jane Doe", 2011, "A lizard", "John Smith", "123 Boring Street", 16000.00);
    SoldArtwork invalidSell = SoldArtwork("Alice Brown", 2011, "A cat", "John Smith", "123 Boring Street", 7000.00);
    
    // populate test data
    collection.insert_artwork(baseArt);

    // test valid sell
    bool result = collection.sell_artwork(soldArt);
    bool passed = assert(
        result &&
            collection.artworks == vector<Artwork>() &&
            collection.soldArtworks == vector<SoldArtwork>({ soldArt }),
        "Art can be sold."
    );

    // test attempt to sell art that does not exist
    result = collection.sell_artwork(invalidSell);
    passed = assert(
        !result && collection.soldArtworks == vector<SoldArtwork>({ soldArt }),
        "Nonexistent art cannot be sold."
    );

    // test attempt to sell art twice
    result = collection.sell_artwork(soldArt);
    passed = assert(
        !result && collection.soldArtworks == vector<SoldArtwork>({ soldArt }),
        "Art cannot be sold twice."
    );

    return passed;
}

int run_tests() {
    ArtworkCollection testCollection = generate_test_data();
    return test_insert_artwork() && test_sell_artwork();
}

int main() {
    cout << "Running tests." << endl;
    return run_tests();
}
