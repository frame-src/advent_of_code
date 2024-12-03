import Foundation

func readFileContent(from fileName: String, at directoryPath: String) -> String {
    let fileManager = FileManager.default

    if fileManager.fileExists(atPath: directoryPath) {
        let directoryURL = URL(fileURLWithPath: directoryPath) 
        let fileURL = directoryURL.appendingPathComponent(fileName)
        do { 
            let fileContents = try String(contentsOf: fileURL, encoding: .utf8)
            return fileContents
        } catch {
            return "Error reading file: \(error)"
        }
    } else {
        return "Failed to find directory: \(directoryPath)"
    }
}

func splitContent(input: String) -> [String] {
    let lines = input.split(separator:"\n").map{String($0)}
    return lines
}


func checkSafety( array: [Int]) -> Bool {
    var i: Int = 0
    let descendingOrder : Bool = (array.first ?? 0) > (array.last ?? 0) ? true : false
    
    while i < (array.count - 1){
        if descendingOrder {
            print(descendingOrder)
            let value = array[i] - array[i + 1]
            print(value)
            if value <= 0 || value > 3 {
                return false
            }
        } else {
            let value = array[i] - array[i + 1]
            print(descendingOrder)
            print(value)
            if value < -3 || value >= 0 {
                return false
            }
        }
        i = i + 1
    }
    return true
}

func processLine(lines: [String]) -> Int {
    var counter : Int = 0
    var check : Bool = false
    var tmp_numbers: [Int] = []
    var i: Int = 0

    for line in lines {
        let numbers = line.split(separator: " ").compactMap { Int($0) }
        check = checkSafety(array : numbers)
        if check == true {
            counter = counter + 1
        } else {
            while i < numbers.count {
                tmp_numbers = numbers
                tmp_numbers.remove(at:i)
                check = checkSafety(array: tmp_numbers)
                if check == true{
                    counter = counter + 1
                    break
                }
                i = i + 1
            }
        }
    }
    return counter
}


func main() {
    let fileName = "input"
    let fileManager = FileManager.default
    let currentDirectoryPath = fileManager.currentDirectoryPath
    var content : String = ""
    content = readFileContent(from: fileName, at: currentDirectoryPath)

    let lines = splitContent( input:content )
    let result = processLine(lines: lines)
    print(result)
}

main()
