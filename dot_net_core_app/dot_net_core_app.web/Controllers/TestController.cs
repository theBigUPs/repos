using Microsoft.AspNetCore.Mvc;

namespace dot_net_core_app.web.Controllers
{
    public class TestController : Controller
    {


        public class Product2
        {
            public int Id { get; set; }
            public string  name { get; set; }
        }


        public IActionResult Index()  //     test/index    view
        {
            var prod_list = new List<Product2>()
            {
                new(){Id=0,name="testprod"},
                new() { Id = 1, name = "real" }
            };
            ViewBag.name = "dffsdffghjkmbmbmbmbmbmn";


            ViewData["age"] = 30;

            ViewData["names"] = new List<string>() { "this", "is", "the", "names", "list" };

            ViewBag.person = new { id = 3, name = "toby", age = 99 };

            TempData["a"] = "testingtesting"; // temptest only displays this if you come to this page first

            return View(prod_list);
        }

        public IActionResult Index2()// test/index2 redirects to index
        {
            return RedirectToAction("Index","Test");
        }

        public IActionResult TempTest()
        {

            return View();

        }

        public IActionResult ParameterView(int id)// test/parameterview/num
        {
            return RedirectToAction("JsonParameter", "Test", new { id = id });
        }

        public IActionResult JsonParameter(int id)
        {
            return Json(new { Id = id });
        }

        public IActionResult ContentResult()// test/contentresult  string
        {
            return Content("hello there"); 
        }

        public IActionResult JsonResult()//  /test/jsonresult  json
        {
            return Json(new { Id=0 , name="hello there", price=12 });
        }

        public IActionResult EmptyResult()// /test/emptyresult   bos sayfa
        {
            
            return new EmptyResult();
        }

    }
}
