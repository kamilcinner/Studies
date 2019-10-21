package com.erteez;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/sq")
public class SqServlet extends HttpServlet
{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException
	{
//		HttpSession session = req.getSession();
//		
////		session.removeAttribute("k");
//		
//		int k = (int)session.getAttribute("k");
		
		int k = 0;
		
		Cookie cookies[] = req.getCookies();
		
		for (Cookie c : cookies)
		{
			if (c.getName().equals("k"))
			{
				k = Integer.parseInt(c.getValue());
				break;
			}
		}
		
		k = k * k;
		
		PrintWriter out = res.getWriter();
		out.println("Result is " + k);
		
		System.out.println("sq called");
	}
}
