package com.example.exam;

import lombok.Data;
@Data
public class Pages {
	Integer pages;
	Integer currentpage;
	Integer pagesize;
	Integer counts;
	public int computePageByCountandPagesize() {
		int pages=0;
		if(this.getCounts()%this.getPagesize()==0) {
			pages=this.getCounts()/this.getPagesize();
		}
		else {
			pages=(int)(this.getCounts()/this.getPagesize())+1;
		}
		this.pages=pages;
		return pages;
	}
}
