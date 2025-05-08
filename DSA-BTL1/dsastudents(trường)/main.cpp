#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "list/listheader.h"

#include "ann/xtensor_lib.h"
#include "ann/dataset.h"
#include "ann/dataloader.h"

using namespace std;

string shape2str(xt::svector<unsigned long> vec)
{
    stringstream ss;
    ss << "(";
    for (int idx = 0; idx < vec.size(); idx++)
    {
        ss << vec[idx] << ", ";
    }
    string res = ss.str();
    if (vec.size() > 1)
        res = res.substr(0, res.rfind(','));
    else
        res = res.substr(0, res.rfind(' '));
    return res + ")";
}

string shape2str(xt::svector<size_t> vec)
{
    stringstream ss;
    ss << "(";
    for (int idx = 0; idx < vec.size(); idx++)
    {
        ss << vec[idx] << ", ";
    }
    string res = ss.str();
    if (vec.size() > 1)
        res = res.substr(0, res.rfind(','));
    else
        res = res.substr(0, res.rfind(' '));
    return res + ")";
}

void case_data_wo_label_1(){
    xt::xarray<int> X = xt::arange<int>(10*4).reshape({10, 4});
    xt::xarray<int> t;
    //Show X and t
    cout << "############################################" << endl;
    cout << "#CASE: data WITHOUT label" << endl;
    cout << "############################################" << endl;
    cout << "ORIGINAL data and label:" << endl;
    cout << "X.shape: " << shape2str(X.shape()) << endl;
    cout << "X: " << endl << X << endl;
    cout << "t.shape: " << shape2str(t.shape()) << endl;
    cout << "t: " << endl << t << endl;
    cout << "=================================" << endl;

    //Create TensorDataset and DataLoader
    TensorDataset<int, int> ds(X, t);
    int batch_size = 3;
    bool shuffle = false, drop_last = false;
    int seed;
    DataLoader<int, int> *pLoader;

    cout << "Loading (1): with shuffle=false:" << endl;
    cout << "################################" << endl;
    shuffle = false;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    int batch_idx = 1;
    for(auto batch: *pLoader){
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:"  << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;

    // cout << "Loading (2): with shuffle=true + no seed (seed < 0):" << endl;
    // cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    // cout << "################################" << endl;
    // shuffle = true;
    // seed = -1;
    // pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    // batch_idx = 1;
    // for(auto batch: *pLoader){
    //     cout << "batch_idx:" << batch_idx++ << endl;
    //     string dshape = shape2str(batch.getData().shape());
    //     string lshape = shape2str(batch.getLabel().shape());
    //     cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
    //     cout << "data:"  << endl << batch.getData() << endl;
    //     cout << "label:" << endl << batch.getLabel() << endl;
    // }
    // cout << endl << endl;
    // delete pLoader;

    // cout << "Loading (3): with shuffle=true + no seed (seed < 0):" << endl;
    // cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    // cout << "################################" << endl;
    // shuffle = true;
    // seed = -1;
    // pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    // batch_idx = 1;
    // for(auto batch: *pLoader){
    //     cout << "batch_idx:" << batch_idx++ << endl;
    //     string dshape = shape2str(batch.getData().shape());
    //     string lshape = shape2str(batch.getLabel().shape());
    //     cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
    //     cout << "data:"  << endl << batch.getData() << endl;
    //     cout << "label:" << endl << batch.getLabel() << endl;
    // }
    // cout << endl << endl;
    // delete pLoader;
    cout << "NOTE: Loading (2) and (3): DO NOT CALL seed; so results are different." << endl;
    cout << endl << endl;

    cout << "Loading (4): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for(auto batch: *pLoader){
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:"  << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;

    cout << "Loading (5): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for(auto batch: *pLoader){
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:"  << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << "NOTE: Loading (4) and (5): CALL xt::random::seed and use SAME seed => same results." << endl;
    cout << endl << endl;
}

	
void case_data_wi_label_1(){
    xt::xarray<int> X = xt::arange<int>(10*4).reshape({10, 4});
    xt::xarray<int> t = xt::arange<int>(10);
    //Show X and t
    cout << "############################################" << endl;
    cout << "#CASE: data WITH label" << endl;
    cout << "WHEN label is available: " << endl;
    cout << "\tAssignment-1: ASSUME that dimension-0 on data = dimension-0 on label" << endl;
    cout << "############################################" << endl;
    cout << "ORIGINAL data and label:" << endl;
    cout << "X.shape: " << shape2str(X.shape()) << endl;
    cout << "X: " << endl << X << endl;
    cout << "t.shape: " << shape2str(t.shape()) << endl;
    cout << "t: " << endl << t << endl;
    cout << "=================================" << endl;

    //Create TensorDataset and DataLoader
    TensorDataset<int, int> ds(X, t);
    int batch_size = 3;
    bool shuffle = false, drop_last = false;
    int seed;
    DataLoader<int, int> *pLoader;

    cout << "Loading (1): with shuffle=false:" << endl;
    cout << "################################" << endl;
    shuffle = false;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    int batch_idx = 1;
    for(auto batch: *pLoader){
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:"  << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    cout << endl << endl;
    delete pLoader;

    // cout << "Loading (2): with shuffle=true + no seed (seed < 0):" << endl;
    // cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    // cout << "################################" << endl;
    // shuffle = true;
    // seed = -1;
    // pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    // batch_idx = 1;
    // for(auto batch: *pLoader){
    //     cout << "batch_idx:" << batch_idx++ << endl;
    //     string dshape = shape2str(batch.getData().shape());
    //     string lshape = shape2str(batch.getLabel().shape());
    //     cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
    //     cout << "data:"  << endl << batch.getData() << endl;
    //     cout << "label:" << endl << batch.getLabel() << endl;
    // }
    // cout << endl << endl;
    // delete pLoader;

    // cout << "Loading (3): with shuffle=true + no seed (seed < 0):" << endl;
    // cout << "when seed < 0: DO NOT call xt::random:seed" << endl;
    // cout << "################################" << endl;
    // shuffle = true;
    // seed = -1;
    // pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    // batch_idx = 1;
    // for(auto batch: *pLoader){
    //     cout << "batch_idx:" << batch_idx++ << endl;
    //     string dshape = shape2str(batch.getData().shape());
    //     string lshape = shape2str(batch.getLabel().shape());
    //     cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
    //     cout << "data:"  << endl << batch.getData() << endl;
    //     cout << "label:" << endl << batch.getLabel() << endl;
    // }
    // cout << endl << endl;
    // delete pLoader;
    cout << "NOTE: Loading (2) and (3): DO NOT CALL seed; so results are different." << endl;
    cout << endl << endl;

    cout << "Loading (4): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for(auto batch: *pLoader){
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:"  << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << endl << endl;

    cout << "Loading (5): with shuffle=true + with seed (seed >= 0):" << endl;
    cout << "when seed >= 0: CALL xt::random:seed" << endl;
    cout << "################################" << endl;
    shuffle = true;
    seed = 100;
    pLoader = new DataLoader<int, int>(&ds, batch_size, shuffle, drop_last, seed);
    batch_idx = 1;
    for(auto batch: *pLoader){
        cout << "batch_idx:" << batch_idx++ << endl;
        string dshape = shape2str(batch.getData().shape());
        string lshape = shape2str(batch.getLabel().shape());
        cout << "(data.shape, label.shape): " << dshape + ", " + lshape << endl;
        cout << "data:"  << endl << batch.getData() << endl;
        cout << "label:" << endl << batch.getLabel() << endl;
    }
    delete pLoader;
    cout << "NOTE: Loading (4) and (5): CALL xt::random::seed and use SAME seed => same results." << endl;
    cout << endl << endl;
}

int main(int argc, char **argv)
{
    case_data_wo_label_1();
    // case_data_wi_label_1();
    return 0;
}