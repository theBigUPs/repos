namespace dot_net_core_app.web.Models
{
    public class ProductRepo
    {
        private List<Product> _products= new List<Product>();


        public List<Product> Products()
        {
            return _products;   
        }

        public void Add(Product NewProduct)
        {
            _products.Add(NewProduct);
        }

        public void Remove(int id)
        {
            var hasProduct=_products.FirstOrDefault(p => p.Id == id);
            if (hasProduct==null)
            {
                throw new Exception($"no product with this id({id})");
            }
            _products.Remove(hasProduct);
        }


        public void Update(Product UpdateProduct)
        {
            var hasProduct = _products.FirstOrDefault(p => p.Id == UpdateProduct.Id);
            if (hasProduct == null)
            {
                throw new Exception($"no product with this id({UpdateProduct.Id})");
            }

            hasProduct.Name = UpdateProduct.Name;
            hasProduct.Price = UpdateProduct.Price;
            hasProduct.Stock = UpdateProduct.Stock;

            var index = _products.FindIndex(p => p.Id == UpdateProduct.Id);
            _products[index] = hasProduct;
        }


    }
}
