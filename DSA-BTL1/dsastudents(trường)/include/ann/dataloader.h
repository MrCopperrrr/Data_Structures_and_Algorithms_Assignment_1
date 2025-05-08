
/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */
#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/dataset.h"
#include "ann/xtensor_lib.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader {
  public:
    class Iterator;//forward declaration
  private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size; 
    bool shuffle;
    bool drop_last;
    //các biến mới
    int Allbatch; 
    xt::xarray<size_t> index_list;
    int m_seed;

  




  public:
  //constructor
    DataLoader(Dataset<DType, LType>* ptr_dataset, 
                                    int batch_size, 
                                    bool shuffle = true, 
                                    bool drop_last = false, 
                                    int seed = -1) {
      this->ptr_dataset = ptr_dataset;
      this->batch_size = batch_size;
      this->shuffle = shuffle;
      this->drop_last = drop_last;
      this->m_seed = seed;

      index_list = xt::arange<size_t>(0, ptr_dataset->len());


      Allbatch = ptr_dataset->len() / batch_size;

      if (drop_last && ptr_dataset->len() % batch_size != 0) {
        int drop_size = ptr_dataset->len() % batch_size;
        index_list = xt::view(index_list, xt::range(0, index_list.size() - drop_size));
      }

      if (shuffle) {//shuffle của trường
        if (m_seed >= 0) {
          xt::random::seed(m_seed); 
        }
        xt::random::shuffle(index_list);
      }

      if (index_list.size() < batch_size) {
          this->batch_size = 0; 
      }

    }
    //hết hàm khởi tạo

  virtual ~DataLoader() {}

  Iterator begin() {
    return Iterator(this, 0);
  }

  Iterator end() {
    return Iterator(this, Allbatch);
  // return Iterator(this, (batch_size == 0) ? 0 : index_list.size());
  }

  //gồm có operator ++, operator !=, operator *, operator =
  class Iterator {
    
    public:
    //operator ++
      Iterator& operator++() {//tăng index lên 1
        index++;
        return *this;
      }
    //operator ++(int)    
      Iterator operator++(int) {//tăng index lên 1 và trả về giá trị cũ của index
        Iterator temp = *this;
        ++*this;
        return temp;
      }
    //operator =
      Iterator& operator=(const Iterator& iterator) {//gán giá trị của iterator cho this
        if (this != &iterator) {//kiểm tra xem có phải là chính nó không
          loader = iterator.loader;
          index = iterator.index;
        }
        return *this;
      }
    //operator !=
      bool operator!=(const Iterator& other) const {//so sánh index
        return index != other.index;
      }

      Iterator(DataLoader* loader, int index) : loader(loader), index(index) {}
    //operator *
      Batch<DType, LType> operator*() const{
        // int batch_start = index * loader->batch_size;
        // int batch_end = batch_start + loader->batch_size;

        if (loader->batch_size == 0 || index >= loader->index_list.size()) {// || index == loader->Allbatch) {
        return Batch<DType, LType>(xt::xarray<DType>{}, xt::xarray<LType>{});//trả về batch rỗng
        }

        size_t startB = index * loader->batch_size;//index của batch bắt đầu
        size_t endB = startB + loader->batch_size;//index của batch kết thúc

        if (index == loader->Allbatch - 1 && !loader->drop_last) {//nếu là batch cuối và không bỏ qua
          endB = loader->ptr_dataset->len();//endB = số lượng phần tử của dataset
        }




        // xt::xarray<size_t> batch_indices = xt::view(loader->index_list, xt::range(batch_start, batch_end));
        xt::xarray<size_t> indexB = xt::view(loader->index_list, xt::range(startB, endB));

        // lấy shape của dataB và labelB
        auto data_shape = loader->ptr_dataset->get_data_shape();
        auto label_shape = loader->ptr_dataset->get_label_shape();


        // cập nhật số lượng phần tử của dataB và labelB
        data_shape[0] = indexB.size();
        label_shape[0] = indexB.size();


        // khởi tạo dataB và labelB
        xt::xarray<DType> dataB = xt::empty<DType>(data_shape);
        xt::xarray<LType> labelB = xt::empty<LType>(label_shape);



        //lặp qua các phần tử của batch để lấy dataB và labelB của từng phần tử
        for (size_t i = 0; i < indexB.size(); i++) {
          DataLabel<DType, LType> data_label = loader->ptr_dataset->getitem(indexB(i));
          xt::view(dataB, i, xt::all()) = data_label.getData();
          xt::view(labelB, i, xt::all()) = data_label.getLabel();
        }
        
        return Batch<DType, LType>(dataB, labelB);
      }






    private:
    DataLoader* loader;
    int index;
  };

};

#endif /* DATALOADER_H */