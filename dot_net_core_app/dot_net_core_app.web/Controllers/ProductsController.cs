using dot_net_core_app.web.Models;
using Microsoft.AspNetCore.Mvc;

namespace dot_net_core_app.web.Controllers
{
    

    public class ProductsController : Controller
    {
        
        private readonly ProductRepo repo;

        public ProductsController()
        {
            
            
            
             repo = new ProductRepo();
            
            

        }


        

        public IActionResult Index()
        {
            
            var products= repo.Products();


            


            return View(products);

        }
        
        
        public IActionResult Remove(int id)
        {
            
            repo.remove(id);
            return RedirectToAction("Index");

            //return View("Index", "Products");

        }

    }
}
